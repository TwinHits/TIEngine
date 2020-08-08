#include "componentsystems/MovesComponentSystem.h" 

#include <cmath>
#include <string>

#include <SFML/Graphics.hpp>

#include "componentsystems/GridComponentSystem.h"
#include "managers/LogManager.h" 
#include "managers/EventsManager.h"
#include "objects/components/MovesComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"
#include "utilities/TIEMath.h"

using namespace TIE;

const std::string MovesComponentSystem::MOVES = "moves";
const std::string MovesComponentSystem::SPEED = "speed";
const std::string MovesComponentSystem::DIRECTION = "direction";
const std::string MovesComponentSystem::ROTATIONSPEED = "rotationSpeed";
const std::string MovesComponentSystem::SPEED_KEY = MovesComponentSystem::MOVES + '.' + MovesComponentSystem::SPEED;
const std::string MovesComponentSystem::DIRECTION_KEY = MovesComponentSystem::MOVES + '.' + MovesComponentSystem::DIRECTION;
const std::string MovesComponentSystem::ROTATIONSPEED_KEY = MovesComponentSystem::MOVES + '.' + MovesComponentSystem::ROTATIONSPEED;
const float MovesComponentSystem::CLOSE_ENOUGH = 0.5f;

void MovesComponentSystem::update(TIEntity& entity, const float delta) {
	MovesComponent* movesComponent = entity.getComponent<MovesComponent>();
	if (movesComponent != nullptr) {
		SpriteComponent* spriteComponent = entity.getComponent<SpriteComponent>();
		if (spriteComponent != nullptr) {
			this->move(*movesComponent, *spriteComponent, delta);
			this->rotate(*movesComponent, *spriteComponent, delta);
		}
	}
}


MovesComponent* MovesComponentSystem::addMovesComponent(const TIEntityFactory& factory, TIEntity& entity) {

	MovesComponent* movesPtr = nullptr;
	if (factory.floatValues.count(MovesComponentSystem::SPEED_KEY)) {
		float speed = factory.floatValues.at(MovesComponentSystem::SPEED_KEY);

		movesPtr = &entity.addComponent<MovesComponent>();

		sf::Vector2f velocity = sf::Vector2f();
		velocity.x = speed;
		if (factory.floatValues.count(MovesComponentSystem::DIRECTION_KEY)) {
			float direction = factory.floatValues.at(MovesComponentSystem::DIRECTION_KEY);
			velocity.y = direction;
		} else {
			velocity.y = 0;
		}
		movesPtr->setVelocity(velocity);
	}

	if (factory.floatValues.count(MovesComponentSystem::ROTATIONSPEED_KEY)) {
		float rotationalSpeed = factory.floatValues.at(MovesComponentSystem::ROTATIONSPEED_KEY);

		if (movesPtr == nullptr) {
			movesPtr = &entity.addComponent<MovesComponent>();
		}

		movesPtr->setAngularVelocity(sf::Vector2f(rotationalSpeed, 0.0f));
	}

	return movesPtr;
}


void MovesComponentSystem::setTargetPosition(TIEntity& tientity, Direction direction) {
	MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	SpriteComponent* spriteComponent = tientity.getComponent<SpriteComponent>();
	if (MovesComponentSystem::arePositionsCloseEnough(movesComponent->getTargetPosition(), spriteComponent->getPosition())) {
		sf::Vector2f targetPosition = spriteComponent->getPosition();
		const sf::Vector2f& velocity = movesComponent->getVelocity();
		if (direction == Direction::TOP) {
			targetPosition += sf::Vector2f(0, -velocity.x);
		} else if (direction == Direction::LEFT) {
			targetPosition += sf::Vector2f(-velocity.x, 0);
		} else if (direction == Direction::RIGHT) {
			targetPosition += sf::Vector2f(velocity.x, 0);
		} else if (direction == Direction::BOTTOM) {
			targetPosition += sf::Vector2f(0, velocity.x);
		}
		MovesComponentSystem::setTargetPosition(tientity, targetPosition);
	}
}


void MovesComponentSystem::setTargetPosition(TIEntity& tientity, sf::Vector2f& position) {
	MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	SpriteComponent* spriteComponent = tientity.getComponent<SpriteComponent>();
	if (movesComponent != nullptr && spriteComponent != nullptr) {
		position = GridComponentSystem::normalizePositionToGrid(position);
		movesComponent->setTargetPosition(position);
		movesComponent->setTargetAngle(Math::angleBetweenTwoPoints(spriteComponent->getPosition(), movesComponent->getTargetPosition()));
	}
}


void MovesComponentSystem::move(MovesComponent& movesComponent, SpriteComponent& spriteComponent, const float delta) {
	if (!MovesComponentSystem::arePositionsCloseEnough(movesComponent.getTargetPosition(), spriteComponent.getPosition())) {
		if (MovesComponentSystem::recalculateVelocity(movesComponent)) {
			movesComponent.setCachedTargetPosition(movesComponent.getTargetPosition());
			movesComponent.setVelocity(sf::Vector2f(movesComponent.getVelocity().x, movesComponent.getTargetAngle()));
		}
		if (MovesComponentSystem::areRotationsCloseEnough(movesComponent.getTargetAngle(), spriteComponent.getRotation())) {
			spriteComponent.sf::Transformable::move(Math::translateVelocityByTime(movesComponent.getVelocity(), delta));
		}
	} else if (spriteComponent.getPosition() != movesComponent.getTargetPosition()) {
		spriteComponent.setPosition(movesComponent.getTargetPosition());
	}
}


void MovesComponentSystem::rotate(MovesComponent& movesComponent, SpriteComponent& spriteComponent, const float delta) {
	if (spriteComponent.getRotation() != movesComponent.getTargetAngle()) {
		if (!MovesComponentSystem::areRotationsCloseEnough(movesComponent.getTargetAngle(), spriteComponent.getRotation())) {
			if (MovesComponentSystem::recalculateAngularVelocity(movesComponent)) {
				movesComponent.setCachedTargetAngle(movesComponent.getTargetAngle());
				movesComponent.setAngularVelocity(sf::Vector2f(movesComponent.getAngularVelocity().x, Math::directionFromAngleToAngle(spriteComponent.getRotation(), movesComponent.getTargetAngle())));
			}
			spriteComponent.sf::Transformable::rotate(Math::translateVelocityByTime(movesComponent.getAngularVelocity(), delta).x * movesComponent.getAngularVelocity().y);
		} else if (spriteComponent.getRotation() != movesComponent.getTargetAngle()) {
			spriteComponent.setRotation(movesComponent.getTargetAngle());
		}
	}
}


bool MovesComponentSystem::arePositionsCloseEnough(const sf::Vector2f& position1, const sf::Vector2f& position2) {
	return Math::distanceBetweenTwoPoints(position1, position2) <= MovesComponentSystem::CLOSE_ENOUGH;
}


bool MovesComponentSystem::areRotationsCloseEnough(const float rotation1, const float rotation2) {
	return Math::distanceBetweenTwoAngles(rotation1, rotation2) <= MovesComponentSystem::CLOSE_ENOUGH;
}


bool MovesComponentSystem::recalculateVelocity(MovesComponent& movesComponent) {
	if (movesComponent.getTargetPosition() != movesComponent.getCachedTargetPosition()) {
		return true;
	}
	return false;
}


bool MovesComponentSystem::recalculateAngularVelocity(MovesComponent& movesComponent) {
	if (!Math::areFloatsEqual(movesComponent.getTargetAngle(), movesComponent.getCachedTargetAngle())) {
		return true;
	}
	return false;
}

