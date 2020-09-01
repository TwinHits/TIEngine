#include "componentsystems/MovesComponentSystem.h" 

#include <cmath>
#include <string>

#include <SFML/Graphics.hpp>

#include "componentsystems/GridComponentSystem.h"
#include "managers/WorldManager.h"
#include "managers/LogManager.h" 
#include "managers/EventsManager.h"
#include "objects/components/MovesComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"
#include "utils/TIEMath.h"

using namespace TIE;

const std::string MovesComponentSystem::MOVES = "moves";
const std::string MovesComponentSystem::MAXSPEED = "maxSpeed";
const std::string MovesComponentSystem::ACCELERATION = "acceleration";
const std::string MovesComponentSystem::ROTATIONSPEED = "rotationSpeed";
const std::string MovesComponentSystem::MAXSPEED_KEY = MovesComponentSystem::MOVES + '.' + MovesComponentSystem::MAXSPEED;
const std::string MovesComponentSystem::ACCELERATION_KEY = MovesComponentSystem::MOVES + '.' + MovesComponentSystem::ACCELERATION;
const std::string MovesComponentSystem::ROTATIONSPEED_KEY = MovesComponentSystem::MOVES + '.' + MovesComponentSystem::ROTATIONSPEED;
const float MovesComponentSystem::CLOSE_ENOUGH = 0.5f;

void MovesComponentSystem::update(const float delta) {
	for (auto& c : components) {
		this->move(c.movesComponent, c.positionComponent, delta);
		this->rotate(c.movesComponent, c.positionComponent, delta);
	}
}


void MovesComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& entity) {
	MovesComponent& movesComponent = entity.addComponent<MovesComponent>();
	PositionComponent& positionComponent = entity.addComponent<PositionComponent>();
	Components components = { movesComponent, positionComponent };

	if (factory.floatValues.count(MovesComponentSystem::MAXSPEED_KEY)) {
		float maxSpeed = factory.floatValues.at(MovesComponentSystem::MAXSPEED_KEY);
		movesComponent.setMaxSpeed(maxSpeed);
	}

	if (factory.floatValues.count(MovesComponentSystem::ACCELERATION_KEY)) {
		float acceleration = factory.floatValues.at(MovesComponentSystem::ACCELERATION_KEY);
		movesComponent.setAcceleration(acceleration);
	}

	if (factory.floatValues.count(MovesComponentSystem::ROTATIONSPEED_KEY)) {
		float rotationalSpeed = factory.floatValues.at(MovesComponentSystem::ROTATIONSPEED_KEY);
		movesComponent.setAngularVelocity(sf::Vector2f(rotationalSpeed, 0.0f));
	}

	movesComponent.setVelocity(sf::Vector2f(movesComponent.getVelocity().x, positionComponent.getAngle()));
	movesComponent.setTargetPosition(positionComponent.getPosition());
	movesComponent.setTargetAngle(positionComponent.getAngle());

	this->components.push_back(components);
}


void MovesComponentSystem::setTargetPosition(MovesComponent& movesComponent, PositionComponent& positionComponent, Direction direction) {
	if (this->arePositionsCloseEnough(movesComponent.getTargetPosition(), positionComponent.getPosition())) {

		float distance = movesComponent.getMaxSpeed();
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
	if (targetPosition != movesComponent.getTargetPosition()) {
		movesComponent.setTargetPosition(targetPosition);
		movesComponent.setTargetAngle(Math::angleBetweenTwoPoints(positionComponent.getPosition(), movesComponent.getTargetPosition()));
	}
}


void MovesComponentSystem::move(MovesComponent& movesComponent, PositionComponent& positionComponent, const float delta) {
	if (!this->arePositionsCloseEnough(movesComponent.getTargetPosition(), positionComponent.getPosition())) {
		this->accelerate(movesComponent, delta);
		sf::Vector2f distance = Math::translateVelocityByTime(movesComponent.getVelocity(), delta);
		sf::Vector2f newPosition = sf::Vector2f(positionComponent.getPosition().x + distance.x, positionComponent.getPosition().y + distance.y);
		positionComponent.setPosition(newPosition);
	} else if (positionComponent.getPosition() != movesComponent.getTargetPosition()) {
		movesComponent.setVelocity(sf::Vector2f(0, movesComponent.getVelocity().y));
		positionComponent.setPosition(movesComponent.getTargetPosition());
	}
}


void MovesComponentSystem::accelerate(MovesComponent& movesComponent, const float delta) {
	if (!Math::areFloatsEqual(movesComponent.getVelocity().x, movesComponent.getMaxSpeed())) {
		if (!this->areFloatsCloseEnough(movesComponent.getVelocity().x, movesComponent.getMaxSpeed())) {
			float speed = movesComponent.getVelocity().x + (movesComponent.getAcceleration() * delta);
			if (speed >= movesComponent.getMaxSpeed()) {
				speed = movesComponent.getMaxSpeed();
			}
			movesComponent.setVelocity(sf::Vector2f(speed, movesComponent.getVelocity().y));
		} else {
			movesComponent.setVelocity(sf::Vector2f(movesComponent.getMaxSpeed(), movesComponent.getVelocity().y));
		}
	}
}


void MovesComponentSystem::rotate(MovesComponent& movesComponent, PositionComponent& positionComponent, const float delta) {
	if (!Math::areFloatsEqual(positionComponent.getAngle(), movesComponent.getTargetAngle())) {
		float angle = positionComponent.getAngle();
		if (!this->areRotationsCloseEnough(positionComponent.getAngle(), movesComponent.getTargetAngle())) {
			movesComponent.setTargetAngle(Math::angleBetweenTwoPoints(positionComponent.getPosition(), movesComponent.getTargetPosition()));
			sf::Vector2f& angularVelocity = movesComponent.getAngularVelocity();
            angularVelocity.y = Math::directionFromAngleToAngle(positionComponent.getAngle(), movesComponent.getTargetAngle());
            movesComponent.setAngularVelocity(angularVelocity);
            angle = positionComponent.getAngle() + (movesComponent.getAngularVelocity().x * movesComponent.getAngularVelocity().y * delta);
		} else {
			angle = movesComponent.getTargetAngle();
        }
		positionComponent.setAngle(angle);
        movesComponent.setVelocity(sf::Vector2f(movesComponent.getVelocity().x, angle));
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

