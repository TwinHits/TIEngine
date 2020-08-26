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
const std::string MovesComponentSystem::SPEED = "speed";
const std::string MovesComponentSystem::DIRECTION = "direction";
const std::string MovesComponentSystem::ROTATIONSPEED = "rotationSpeed";
const std::string MovesComponentSystem::SPEED_KEY = MovesComponentSystem::MOVES + '.' + MovesComponentSystem::SPEED;
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

	if (factory.floatValues.count(MovesComponentSystem::SPEED_KEY)) {
		float speed = factory.floatValues.at(MovesComponentSystem::SPEED_KEY);

		sf::Vector2f velocity = sf::Vector2f();
		velocity.x = speed;
		if (factory.floatValues.count(MovesComponentSystem::DIRECTION_KEY)) {
			float direction = factory.floatValues.at(MovesComponentSystem::DIRECTION_KEY);
			velocity.y = direction;
		} else {
			velocity.y = 0;
		}
		movesComponent.setVelocity(velocity);
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
		spriteComponent.sf::Transformable::move(Math::translateVelocityByTime(movesComponent.getVelocity(), delta));
	} else if (spriteComponent.getPosition() != movesComponent.getTargetPosition()) {
		spriteComponent.setPosition(movesComponent.getTargetPosition());
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
		} else if (this->areRotationsCloseEnough(velocity.y, movesComponent.getTargetAngle())) {
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

