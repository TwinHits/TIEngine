#include "componentsystems/MovesComponentSystem.h" 

#include <cmath>
#include <string>

#include <SFML/Graphics.hpp>

#include "componentsystems/GridComponentSystem.h"
#include "managers/WorldManager.h"
#include "managers/LogManager.h" 
#include "managers/EventsManager.h"
#include "objects/components/MovesComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"
#include "utils/TIEMath.h"

using namespace TIE;

const std::string MovesComponentSystem::MOVES = "moves";
const std::string MovesComponentSystem::MAXSPEED = "maxSpeed";
const std::string MovesComponentSystem::ACCELERATION = "acceleration";
const std::string MovesComponentSystem::DIRECTION = "direction";
const std::string MovesComponentSystem::ROTATIONSPEED = "rotationSpeed";
const std::string MovesComponentSystem::MAXSPEED_KEY = MovesComponentSystem::MOVES + '.' + MovesComponentSystem::MAXSPEED;
const std::string MovesComponentSystem::ACCELERATION_KEY = MovesComponentSystem::MOVES + '.' + MovesComponentSystem::ACCELERATION;
const std::string MovesComponentSystem::DIRECTION_KEY = MovesComponentSystem::MOVES + '.' + MovesComponentSystem::DIRECTION;
const std::string MovesComponentSystem::ROTATIONSPEED_KEY = MovesComponentSystem::MOVES + '.' + MovesComponentSystem::ROTATIONSPEED;
const float MovesComponentSystem::CLOSE_ENOUGH = 0.5f;

void MovesComponentSystem::update(const float delta) {
	for (auto& c : components) {
		this->move(c.movesComponent, c.spriteComponent, delta);
		this->rotate(c.movesComponent, c.spriteComponent, delta);
	}
}


void MovesComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& entity) {
	MovesComponent& movesComponent = entity.addComponent<MovesComponent>();
	SpriteComponent& spriteComponent = entity.addComponent<SpriteComponent>();
	Components components = { movesComponent, spriteComponent };

	if (factory.floatValues.count(MovesComponentSystem::MAXSPEED_KEY)) {
		float maxSpeed = factory.floatValues.at(MovesComponentSystem::MAXSPEED_KEY);
		movesComponent.setMaxSpeed(maxSpeed);
	}

	if (factory.floatValues.count(MovesComponentSystem::ACCELERATION_KEY)) {
		float acceleration = factory.floatValues.at(MovesComponentSystem::ACCELERATION_KEY);
		movesComponent.setAcceleration(acceleration);
	}

	if (factory.floatValues.count(MovesComponentSystem::DIRECTION_KEY)) {
        float direction = factory.floatValues.at(MovesComponentSystem::DIRECTION_KEY);
		movesComponent.setVelocity(sf::Vector2f(0, direction));
	}

	if (factory.floatValues.count(MovesComponentSystem::ROTATIONSPEED_KEY)) {
		float rotationalSpeed = factory.floatValues.at(MovesComponentSystem::ROTATIONSPEED_KEY);
		movesComponent.setAngularVelocity(sf::Vector2f(rotationalSpeed, 0.0f));
	}

	this->components.push_back(components);
}


void MovesComponentSystem::setTargetPosition(MovesComponent& movesComponent, SpriteComponent& spriteComponent, Direction direction) {
	if (this->arePositionsCloseEnough(movesComponent.getTargetPosition(), spriteComponent.getPosition())) {

		sf::Vector2f velocity = movesComponent.getVelocity();
		if (WorldManager::Instance()->isGridConfigured()) {
			const sf::Vector2f& tileSize = WorldManager::Instance()->getGridComponent()->getTileSize();
			velocity.x = tileSize.x;
		}

		sf::Vector2f targetPosition = spriteComponent.getPosition();
		if (direction == Direction::TOP) {
			targetPosition += sf::Vector2f(0, -velocity.x);
		} else if (direction == Direction::LEFT) {
			targetPosition += sf::Vector2f(-velocity.x, 0);
		} else if (direction == Direction::RIGHT) {
			targetPosition += sf::Vector2f(velocity.x, 0);
		} else if (direction == Direction::BOTTOM) {
			targetPosition += sf::Vector2f(0, velocity.x);
		}
		this->setTargetPosition(movesComponent, spriteComponent, targetPosition);
	}
}


void MovesComponentSystem::setTargetPosition(MovesComponent& movesComponent, SpriteComponent& spriteComponent, sf::Vector2f& position) {
	position = GridComponentSystem::Instance()->normalizePositionToGrid(position);
	if (position != movesComponent.getTargetPosition()) {
		movesComponent.setTargetPosition(position);
		movesComponent.setTargetAngle(Math::angleBetweenTwoPoints(spriteComponent.getPosition(), movesComponent.getTargetPosition()));
	}
}


void MovesComponentSystem::move(MovesComponent& movesComponent, SpriteComponent& spriteComponent, const float delta) {
	if (!this->arePositionsCloseEnough(movesComponent.getTargetPosition(), spriteComponent.getPosition())) {
		this->accelerate(movesComponent, delta);
		spriteComponent.sf::Transformable::move(Math::translateVelocityByTime(movesComponent.getVelocity(), delta));
	} else if (spriteComponent.getPosition() != movesComponent.getTargetPosition()) {
		movesComponent.setVelocity(sf::Vector2f(0, movesComponent.getVelocity().y));
		spriteComponent.setPosition(movesComponent.getTargetPosition());
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


void MovesComponentSystem::rotate(MovesComponent& movesComponent, SpriteComponent& spriteComponent, const float delta) {
    sf::Vector2f& velocity = movesComponent.getVelocity();
	if (!Math::areFloatsEqual(velocity.y, movesComponent.getTargetAngle())) {
		if (!this->areRotationsCloseEnough(velocity.y, movesComponent.getTargetAngle())) {
			sf::Vector2f& angularVelocity = movesComponent.getAngularVelocity();
            movesComponent.setTargetAngle(Math::angleBetweenTwoPoints(spriteComponent.getPosition(), movesComponent.getTargetPosition()));
            angularVelocity.y = Math::directionFromAngleToAngle(velocity.y, movesComponent.getTargetAngle());
            movesComponent.setAngularVelocity(angularVelocity);
            velocity.y = velocity.y + (movesComponent.getAngularVelocity().x * movesComponent.getAngularVelocity().y * delta);
		} else {
			velocity.y = movesComponent.getTargetAngle();
        }
        movesComponent.setVelocity(velocity);
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

