#include "componentsystems/MovesComponentSystem.h" 

#include <cmath>
#include <string>

#include <SFML/Graphics.hpp>

#include "componentsystems/GridComponentSystem.h"
#include "managers/WorldManager.h"
#include "managers/LogManager.h" 
#include "objects/components/MovesComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"
#include "utils/TIEMath.h"

using namespace TIE;

const std::string MovesComponentSystem::MOVES = "moves";
const std::string MovesComponentSystem::MAXSPEED = "moves.maxSpeed";
const std::string MovesComponentSystem::ACCELERATION = "moves.acceleration";
const std::string MovesComponentSystem::ROTATIONSPEED = "moves.rotationSpeed";
const float MovesComponentSystem::CLOSE_ENOUGH = 0.5f;

void MovesComponentSystem::update(const float delta) {
	for (auto& c : components) {
		this->move(c.movesComponent, c.positionComponent, delta);
		this->rotate(c.movesComponent, c.positionComponent, delta);
	}
}


void MovesComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
	MovesComponent& movesComponent = tientity.addComponent<MovesComponent>();
	PositionComponent& positionComponent = tientity.addComponent<PositionComponent>();
	Components components = { movesComponent, positionComponent };

	if (factory.floatValues.count(MovesComponentSystem::MAXSPEED)) {
		float maxSpeed = factory.floatValues.at(MovesComponentSystem::MAXSPEED);
		movesComponent.maxSpeed = maxSpeed;
	}

	if (factory.floatValues.count(MovesComponentSystem::ACCELERATION)) {
		float acceleration = factory.floatValues.at(MovesComponentSystem::ACCELERATION);
		movesComponent.acceleration = acceleration;
	}

	if (factory.floatValues.count(MovesComponentSystem::ROTATIONSPEED)) {
		float rotationalSpeed = factory.floatValues.at(MovesComponentSystem::ROTATIONSPEED);
		movesComponent.angularVelocity.x = rotationalSpeed;
	}

	movesComponent.targetPosition = positionComponent.getPosition();
	movesComponent.targetAngle = positionComponent.getAngle();

	this->components.push_back(components);
}


void MovesComponentSystem::setTargetPosition(MovesComponent& movesComponent, PositionComponent& positionComponent, Direction direction) {
	if (this->arePositionsCloseEnough(movesComponent.targetPosition, positionComponent.getPosition())) {

		float distance = movesComponent.maxSpeed;
		if (WorldManager::Instance()->isGridConfigured()) {
			const sf::Vector2f& tileSize = WorldManager::Instance()->getGridComponent()->getTileSize();
			distance = tileSize.x;
		}

		sf::Vector2f targetPosition = positionComponent.getPosition();
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
		movesComponent.targetAngle = Math::angleBetweenTwoPoints(positionComponent.getPosition(), movesComponent.targetPosition);
	}
}


void MovesComponentSystem::move(MovesComponent& movesComponent, PositionComponent& positionComponent, const float delta) {
	if (!this->arePositionsCloseEnough(movesComponent.targetPosition, positionComponent.getPosition())) {
		this->accelerate(movesComponent, delta);
		movesComponent.targetAngle = Math::angleBetweenTwoPoints(positionComponent.getPosition(), movesComponent.targetPosition);
		sf::Vector2f velocity = sf::Vector2f(movesComponent.speed, positionComponent.getAngle());
		sf::Vector2f distance = Math::translateVelocityByTime(velocity, delta);
		sf::Vector2f newPosition = sf::Vector2f(positionComponent.getPosition().x + distance.x, positionComponent.getPosition().y + distance.y);
		positionComponent.setPosition(newPosition);
	} else if (positionComponent.getPosition() != movesComponent.targetPosition) {
		positionComponent.setPosition(movesComponent.targetPosition);
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
		if (!this->areRotationsCloseEnough(positionComponent.getAngle(), movesComponent.targetAngle)) {
            movesComponent.angularVelocity.y = Math::directionFromAngleToAngle(positionComponent.getAngle(), movesComponent.targetAngle);
			positionComponent.setAngle(positionComponent.getAngle() + movesComponent.angularVelocity.x * movesComponent.angularVelocity.y * delta);
		} else {
			positionComponent.setAngle(movesComponent.targetAngle);
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

