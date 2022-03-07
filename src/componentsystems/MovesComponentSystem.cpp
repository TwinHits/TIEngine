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
    MovesComponent& movesComponent = tientity.addComponent<MovesComponent>();
    PositionComponent& positionComponent = tientity.addComponent<PositionComponent>();
    Components components = { movesComponent, positionComponent };
    this->components.push_back(components);

	float targetSpeed = ComponentSystems::getFactoryValue<float>(factory, MovesComponentSystem::SPEED, movesComponent.targetSpeed, tientity);
	float acceleration = ComponentSystems::getFactoryValue<float>(factory, MovesComponentSystem::ACCELERATION, movesComponent.acceleration, tientity);
	float rotates = ComponentSystems::getFactoryValue<bool>(factory, MovesComponentSystem::ROTATES, movesComponent.rotates, tientity);
	float rotationalSpeed = ComponentSystems::getFactoryValue<float>(factory, MovesComponentSystem::ROTATIONSPEED, movesComponent.rotationalVelocity.x, tientity);

    movesComponent.acceleration = acceleration;
    movesComponent.targetSpeed = targetSpeed;
	movesComponent.rotates = rotates;
	movesComponent.rotationalVelocity.x = rotationalSpeed;
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


bool MovesComponentSystem::setComponentProperty(const std::string& key, bool value, TIEntity& tientity) {
    MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	if (movesComponent != nullptr) {
		if (key == MovesComponentSystem::ROTATES) {
			movesComponent->rotates = value;
		}
	}
    return false;
}


bool MovesComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity)  {
    MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
    if (movesComponent != nullptr) {
        if (key == MovesComponentSystem::SPEED) {
			movesComponent->targetSpeed = value;
		} else if (key == MovesComponentSystem::ACCELERATION) {
			movesComponent->acceleration = value;
		} else if (key == MovesComponentSystem::ROTATIONSPEED) {
			movesComponent->rotationalVelocity.x = value;
		}
    }
    return false;
}


bool MovesComponentSystem::setComponentProperty(const std::string& key, const std::string& value, TIEntity& tientity)  {
    return false;
}


void MovesComponentSystem::setTargetPosition(TIEntity& tientity, sf::Vector2f& targetPosition) {
	MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();
	if (movesComponent != nullptr && positionComponent != nullptr) {

		if (WorldManager::Instance()->isGridConfigured()) {
			targetPosition = GridComponentSystem::Instance()->normalizePositionToGrid(targetPosition);
		}

		movesComponent->hasTargetPosition = true;
		movesComponent->targetPosition = targetPosition;
	}
}


void MovesComponentSystem::setTargetPosition(TIEntity& tientity, float distance) {
	MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();
	if (movesComponent != nullptr && positionComponent != nullptr) {

		sf::Vector2f velocity = sf::Vector2f(distance, positionComponent->rotation);
		sf::Vector2f distance = Math::translateVelocityByTime(velocity,  1);
		sf::Vector2f destination = sf::Vector2f(positionComponent->position.x + distance.x, positionComponent->position.y + distance.y);

		MovesComponentSystem::Instance()->setTargetPosition(tientity, destination);
	}
}


void MovesComponentSystem::setTargetPosition(TIEntity& tientity, Direction direction) {
	MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();

	if (movesComponent != nullptr && positionComponent != nullptr) {
		if (this->atTargetPosition(*movesComponent, *positionComponent)) {

			float distance = movesComponent->targetSpeed;
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
	bool atTargetPosition = Math::areVectorsEqual(movesComponent.targetPosition, positionComponent.position);
	return atTargetPosition;
}


bool MovesComponentSystem::atTargetSpeed(MovesComponent& movesComponent) {
	return Math::areFloatsEqual(movesComponent.speed, movesComponent.targetSpeed);
}


void MovesComponentSystem::move(MovesComponent& movesComponent, PositionComponent& positionComponent, const float delta) {
	if (movesComponent.speed > 0.0f) {
		if (!movesComponent.hasTargetPosition || !this->atTargetPosition(movesComponent, positionComponent)) {
			sf::Vector2f velocity = sf::Vector2f(movesComponent.speed, positionComponent.rotation);
			sf::Vector2f distance = Math::translateVelocityByTime(velocity, delta);
			sf::Vector2f newPosition = sf::Vector2f(positionComponent.position.x + distance.x, positionComponent.position.y + distance.y);
			if (movesComponent.hasTargetPosition && Math::isVectorBetweenVectors(positionComponent.position, newPosition, movesComponent.targetPosition)) {
				positionComponent.position = movesComponent.targetPosition;
			} else {
				positionComponent.position = newPosition;
			}
		}
	}
}


void MovesComponentSystem::accelerate(MovesComponent& movesComponent, PositionComponent& positionComponent, const float delta) {
	float distanceToTarget = movesComponent.lastDistanceToTarget;
	if (movesComponent.hasTargetPosition) {
		distanceToTarget = Math::distanceBetweenTwoPoints(positionComponent.position, movesComponent.targetPosition);
	}

    float direction = 1.0f;
	float acceleration = movesComponent.acceleration;
    if (distanceToTarget > movesComponent.lastDistanceToTarget || movesComponent.targetSpeed < movesComponent.speed) {
        direction = -1.0f;
        acceleration = acceleration * 2 * direction;
    }
    movesComponent.lastDistanceToTarget = distanceToTarget;

	if (movesComponent.speed < movesComponent.targetSpeed) {
		movesComponent.speed = movesComponent.speed + movesComponent.acceleration * delta;
		movesComponent.speed = fmaxf(0.0f, movesComponent.speed);

		if (movesComponent.rotates) {
			if (movesComponent.speed > 0) {
				// Coefficent should decrease for smaller objects and increase for larger objects
				movesComponent.rotationalVelocity.x = movesComponent.targetSpeed - movesComponent.speed * .5;
			} else {
				movesComponent.rotationalVelocity.x = 0;
			}
		}
	}
}


void MovesComponentSystem::rotate(MovesComponent& movesComponent, PositionComponent& positionComponent, const float delta) {
	if (!Math::areFloatsEqual(movesComponent.rotationalVelocity.x, 0)) {
		
		if (movesComponent.hasTargetPosition && !this->atTargetPosition(movesComponent, positionComponent)) {
			movesComponent.targetRotation = Math::angleBetweenTwoPoints(positionComponent.position, movesComponent.targetPosition);
		}

		if (!Math::areFloatsEqual(positionComponent.rotation, movesComponent.targetRotation)) {
			movesComponent.rotationalVelocity.y = Math::directionFromAngleToAngle(positionComponent.rotation, movesComponent.targetRotation);
			float distance = movesComponent.rotationalVelocity.x * movesComponent.rotationalVelocity.y * delta;
			float newRotation = positionComponent.rotation + distance;
			if (!Math::isAngleBetweenAngles(movesComponent.targetRotation, positionComponent.rotation, newRotation)) {
				positionComponent.rotation = newRotation;
			} else {
				positionComponent.rotation = movesComponent.targetRotation;
			}
		}
	}
} 