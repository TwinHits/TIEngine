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
const std::string MovesComponentSystem::SPEED_KEY = MovesComponentSystem::MOVES + '.' + MovesComponentSystem::SPEED;
const std::string MovesComponentSystem::DIRECTION_KEY = MovesComponentSystem::MOVES + '.' + MovesComponentSystem::DIRECTION;
const float MovesComponentSystem::CLOSE_ENOUGH = 0.5f;

void MovesComponentSystem::update(TIEntity& entity, const float delta) {
	MovesComponent* movesComponent = entity.getComponent<MovesComponent>();
	if (movesComponent != nullptr) {
		SpriteComponent* spriteComponent = entity.getComponent<SpriteComponent>();
		if (spriteComponent != nullptr) {
			this->move(*movesComponent, *spriteComponent, delta);
		}
	}
}


MovesComponent* MovesComponentSystem::addMovesComponent(const TIEntityFactory& factory, TIEntity& entity) {

	MovesComponent* movesPtr = nullptr;
	if (factory.floatValues.count(MovesComponentSystem::SPEED_KEY)) {
		float speed = factory.floatValues.at(MovesComponentSystem::SPEED_KEY);
		MovesComponent& movesComponent = entity.addComponent<MovesComponent>();

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

	return movesPtr;
}


void MovesComponentSystem::setDestination(TIEntity& tientity, Direction direction) {
	MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	SpriteComponent* spriteComponent = tientity.getComponent<SpriteComponent>();
	if (MovesComponentSystem::arePositionsCloseEnough(movesComponent->getDestination(), spriteComponent->getPosition())) {
		sf::Vector2f destination = spriteComponent->getPosition();
		const sf::Vector2f& velocity = movesComponent->getVelocity();
		if (direction == Direction::TOP) {
			destination += sf::Vector2f(0, -velocity.x);
		} else if (direction == Direction::LEFT) {
			destination += sf::Vector2f(-velocity.x, 0);
		} else if (direction == Direction::RIGHT) {
			destination += sf::Vector2f(velocity.x, 0);
		} else if (direction == Direction::BOTTOM) {
			destination += sf::Vector2f(0, velocity.x);
		}
		MovesComponentSystem::setDestination(tientity, destination);
	}
}


void MovesComponentSystem::setDestination(TIEntity& tientity, sf::Vector2f& position) {
	MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	if (movesComponent != nullptr) {
		position = GridComponentSystem::normalizePositionToGrid(position);
		movesComponent->setDestination(position);
	}
}


void MovesComponentSystem::move(MovesComponent& movesComponent, SpriteComponent& spriteComponent, const float delta) {
	if (!MovesComponentSystem::arePositionsCloseEnough(movesComponent.getDestination(), spriteComponent.getPosition())) {
		if (movesComponent.recalculateVelocity()) {
			movesComponent.setVelocity(sf::Vector2f(movesComponent.getVelocity().x, Math::angleBetweenTwoPoints(spriteComponent.getPosition(), movesComponent.getDestination())));
		}
		spriteComponent.sf::Transformable::move(Math::translateVelocityByTime(movesComponent.getVelocity(), delta));
	} else if (spriteComponent.getPosition() != movesComponent.getDestination()) {
		spriteComponent.setPosition(movesComponent.getDestination());
	}
}


bool MovesComponentSystem::arePositionsCloseEnough(const sf::Vector2f& position1, const sf::Vector2f& position2) {
	return Math::distanceBetweenTwoPoints(position1, position2) <= MovesComponentSystem::CLOSE_ENOUGH;
}
