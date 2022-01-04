#include "componentsystems/MovesComponentSystem.h" 

#include <cmath>
#include <string>

#include <SFML/Graphics.hpp>

#include "componentsystems/GridComponentSystem.h"
#include "managers/LogManager.h" 
#include "managers/WorldManager.h"
#include "objects/components/MovesComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"
#include "utils/ComponentSystems.h"
#include "utils/TIEMath.h"

using namespace TIE;

void MovesComponentSystem::update(const float delta) {
	for (auto& c : components) {
		this->accelerate(c.movesComponent, c.positionComponent, delta);
		this->rotate(c.movesComponent, c.positionComponent, delta);
		this->move(c.movesComponent, c.positionComponent, delta);
	}
}


void MovesComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {

	float maxSpeed = ComponentSystems::getFactoryValue<float>(factory, MovesComponentSystem::MAXSPEED, 0.0F, tientity);
	float acceleration = ComponentSystems::getFactoryValue<float>(factory, MovesComponentSystem::ACCELERATION, 0.0F, tientity);
	float rotationalSpeed = ComponentSystems::getFactoryValue<float>(factory, MovesComponentSystem::ROTATIONSPEED, 0.0F, tientity);

	if (maxSpeed || acceleration || maxSpeed) {
		MovesComponent& movesComponent = tientity.addComponent<MovesComponent>();
		PositionComponent& positionComponent = tientity.addComponent<PositionComponent>();
		Components components = { movesComponent, positionComponent };

        movesComponent.acceleration = acceleration;
        movesComponent.maxSpeed = maxSpeed;

        this->components.push_back(components);
	}
}


bool MovesComponentSystem::removeComponent(TIEntity& tientity) {
	MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	if (movesComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->movesComponent == movesComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<MovesComponent>();
	} else {
		return false;
	}
}


const std::string& MovesComponentSystem::getName() {
	return MovesComponentSystem::MOVES;
}


void MovesComponentSystem::setTargetPosition(TIEntity& tientity, Direction direction) {
	MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();

	if (movesComponent != nullptr && positionComponent != nullptr) {
		if (this->atTargetPosition(*movesComponent, *positionComponent)) {

			float distance = movesComponent->maxSpeed;
			if (WorldManager::Instance()->isGridConfigured()) {
				const sf::Vector2f& tileSize = WorldManager::Instance()->getGridComponent()->getTileSize();
				distance = tileSize.x;
			}

			sf::Vector2f targetPosition = positionComponent->position;
			if (direction == Direction::TOP) {
				targetPosition += sf::Vector2f(0, -distance);
			} else if (direction == Direction::LEFT) {
				targetPosition += sf::Vector2f(-distance, 0);
			} else if (direction == Direction::RIGHT) {
				targetPosition += sf::Vector2f(distance, 0);
			} else if (direction == Direction::BOTTOM) {
				targetPosition += sf::Vector2f(0, distance);
			}

			this->setTargetPosition(tientity, targetPosition);
		}
	}
}


void MovesComponentSystem::setTargetPosition(TIEntity& tientity, sf::Vector2f& targetPosition) {
	MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();
	if (movesComponent != nullptr && positionComponent != nullptr) {

		if (WorldManager::Instance()->isGridConfigured()) {
			targetPosition = GridComponentSystem::Instance()->normalizePositionToGrid(targetPosition);
		}

		movesComponent->targetPosition = targetPosition;
        movesComponent->targetAngle = Math::angleBetweenTwoPoints(positionComponent->position, movesComponent->targetPosition);
	}
}


bool MovesComponentSystem::atTargetPosition(TIEntity& tientity) {
    MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
    PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();
    if (movesComponent != nullptr && positionComponent != nullptr) {
		return this->atTargetPosition(*movesComponent, *positionComponent);
	} else {
		return false;
	}
}


bool MovesComponentSystem::atTargetPosition(MovesComponent& movesComponent, PositionComponent& positionComponent) {
	return Math::areVectorsEqual(movesComponent.targetPosition, positionComponent.position);
}


void MovesComponentSystem::move(MovesComponent& movesComponent, PositionComponent& positionComponent, const float delta) {
	if (movesComponent.speed != 0) {
        if (!this->atTargetPosition(movesComponent, positionComponent)) {
            sf::Vector2f velocity = sf::Vector2f(movesComponent.speed, positionComponent.angle);
            sf::Vector2f distance = Math::translateVelocityByTime(velocity, delta);
            sf::Vector2f newPosition = sf::Vector2f(positionComponent.position.x + distance.x, positionComponent.position.y + distance.y);
            if (Math::isVectorBetweenVectors(positionComponent.position, newPosition, movesComponent.targetPosition)) {
                positionComponent.position = movesComponent.targetPosition;
            } else {
                positionComponent.position = newPosition;
            }
        } else {
            positionComponent.position = movesComponent.targetPosition;
        }
	}
}


void MovesComponentSystem::accelerate(MovesComponent& movesComponent, PositionComponent& positionComponent,  const float delta) {
	if (!this->atTargetPosition(movesComponent, positionComponent)) {
		float distanceToTarget = Math::distanceBetweenTwoPoints(positionComponent.position, movesComponent.targetPosition);

		float direction = 1.0f;
		float acceleration = movesComponent.acceleration;
		if (distanceToTarget > movesComponent.lastDistanceToTarget) {
			direction = -1.0f;
			acceleration = acceleration * 2;
		}

		movesComponent.speed = movesComponent.speed + movesComponent.acceleration * delta * direction;
		movesComponent.speed = fminf(movesComponent.maxSpeed, movesComponent.speed);
		movesComponent.speed = fmaxf(0.0f, movesComponent.speed);
		movesComponent.lastDistanceToTarget = distanceToTarget;

		if (movesComponent.speed > 0) {
			// Coefficent should decrease for smaller objects and increase for larger objects
			movesComponent.rotationalVelocity.x = movesComponent.maxSpeed - movesComponent.speed * .5;
		} else {
			movesComponent.rotationalVelocity.x = 0;
		}
	} else {
		movesComponent.speed = 0;
		movesComponent.rotationalVelocity.x = 0;
	}
}


void MovesComponentSystem::rotate(MovesComponent& movesComponent, PositionComponent& positionComponent, const float delta) {
	if (movesComponent.rotationalVelocity.x != 0) {
		movesComponent.targetAngle = Math::angleBetweenTwoPoints(positionComponent.position, movesComponent.targetPosition);
		if (!Math::areFloatsEqual(positionComponent.angle, movesComponent.targetAngle)) {
			movesComponent.rotationalVelocity.y = Math::directionFromAngleToAngle(positionComponent.angle, movesComponent.targetAngle);
			float distance = movesComponent.rotationalVelocity.x * movesComponent.rotationalVelocity.y * delta;
			float newAngle = positionComponent.angle + distance;
			if (!Math::isAngleBetweenAngles(movesComponent.targetAngle, positionComponent.angle, newAngle)) {
				positionComponent.angle = newAngle;
			} else {
				positionComponent.angle = movesComponent.targetAngle;
			}
		} else {
			positionComponent.angle = movesComponent.targetAngle;
		}
	}
} 