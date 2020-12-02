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
		this->move(c.movesComponent, c.positionComponent, delta);
		this->rotate(c.movesComponent, c.positionComponent, delta);
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

        movesComponent.angularVelocity.x = rotationalSpeed;
        movesComponent.acceleration = acceleration;
        movesComponent.maxSpeed = maxSpeed;

        this->components.push_back(components);
	}
}


const std::string& MovesComponentSystem::getName() {
	return MovesComponentSystem::MOVES;
}


void MovesComponentSystem::setTargetPosition(MovesComponent& movesComponent, PositionComponent& positionComponent, Direction direction) {
	if (this->arePositionsCloseEnough(movesComponent.targetPosition, positionComponent.position)) {

		float distance = movesComponent.maxSpeed;
		if (WorldManager::Instance()->isGridConfigured()) {
			const sf::Vector2f& tileSize = WorldManager::Instance()->getGridComponent()->getTileSize();
			distance = tileSize.x;
		}

		sf::Vector2f targetPosition = positionComponent.position;
		if (direction == Direction::TOP) {
			targetPosition += sf::Vector2f(0, -distance);
		} else if (direction == Direction::LEFT) {
			targetPosition += sf::Vector2f(-distance, 0);
		} else if (direction == Direction::RIGHT) {
			targetPosition += sf::Vector2f(distance, 0);
		} else if (direction == Direction::BOTTOM) {
			targetPosition += sf::Vector2f(0, distance);
		}
		this->setTargetPosition(movesComponent, positionComponent, targetPosition);
	}
}


void MovesComponentSystem::setTargetPosition(MovesComponent& movesComponent, PositionComponent& positionComponent, sf::Vector2f& targetPosition) {
	targetPosition = GridComponentSystem::Instance()->normalizePositionToGrid(targetPosition);
	if (targetPosition != movesComponent.targetPosition) {
		movesComponent.targetPosition = targetPosition;
		movesComponent.targetAngle = Math::angleBetweenTwoPoints(positionComponent.position, movesComponent.targetPosition);
	}
}

bool MovesComponentSystem::atTargetPosition(TIEntity& tientity) {
    MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
    PositionComponent* positionComponent = tientity.getComponent<PositionComponent>();
    if (movesComponent != nullptr && positionComponent != nullptr) {
		return this->arePositionsCloseEnough(movesComponent->targetPosition, positionComponent->position);
	} else {
		return false;
	}
}


void MovesComponentSystem::move(MovesComponent& movesComponent, PositionComponent& positionComponent, const float delta) {
	if (!this->arePositionsCloseEnough(movesComponent.targetPosition, positionComponent.position)) {
		this->accelerate(movesComponent, delta);
		movesComponent.targetAngle = Math::angleBetweenTwoPoints(positionComponent.position, movesComponent.targetPosition);
		sf::Vector2f velocity = sf::Vector2f(movesComponent.speed, positionComponent.angle);
		sf::Vector2f distance = Math::translateVelocityByTime(velocity, delta);
		sf::Vector2f newPosition = sf::Vector2f(positionComponent.position.x + distance.x, positionComponent.position.y + distance.y);
		positionComponent.position = newPosition;
	} else if (positionComponent.position != movesComponent.targetPosition) {
		positionComponent.position = movesComponent.targetPosition;
		movesComponent.speed = 0;
	}
}


void MovesComponentSystem::accelerate(MovesComponent& movesComponent, const float delta) {
    if (!this->areFloatsCloseEnough(movesComponent.speed, movesComponent.maxSpeed)) {
        movesComponent.speed = movesComponent.speed + movesComponent.acceleration * delta;
        if (movesComponent.speed >= movesComponent.maxSpeed) {
            movesComponent.speed = movesComponent.maxSpeed;
        }
    } else {
        movesComponent.speed = movesComponent.maxSpeed;
    }
}


void MovesComponentSystem::rotate(MovesComponent& movesComponent, PositionComponent& positionComponent, const float delta) {
    if (!this->areRotationsCloseEnough(positionComponent.angle, movesComponent.targetAngle)) {
        movesComponent.angularVelocity.y = Math::directionFromAngleToAngle(positionComponent.angle, movesComponent.targetAngle);
        positionComponent.angle = positionComponent.angle + movesComponent.angularVelocity.x * movesComponent.angularVelocity.y * delta;
    } else {
        positionComponent.angle = movesComponent.targetAngle;
    }
}


bool MovesComponentSystem::arePositionsCloseEnough(const sf::Vector2f& position1, const sf::Vector2f& position2) {
	return Math::distanceBetweenTwoPoints(position1, position2) <= MovesComponentSystem::CLOSE_ENOUGH;
}


bool MovesComponentSystem::areRotationsCloseEnough(const float rotation1, const float rotation2) {
	return Math::distanceBetweenTwoAngles(rotation1, rotation2) <= MovesComponentSystem::CLOSE_ENOUGH;
}


bool MovesComponentSystem::areFloatsCloseEnough(const float f1, const float f2) {
	return fabsf(f1 - f2) <= MovesComponentSystem::CLOSE_ENOUGH;
}

