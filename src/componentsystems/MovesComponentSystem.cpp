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

void MovesComponentSystem::update(TIEntity& entity, const float delta) {
	MovesComponent* movesComponent = entity.getComponent<MovesComponent>();
	if (movesComponent != nullptr) {
		SpriteComponent* spriteComponent = entity.getComponent<SpriteComponent>();
		if (spriteComponent != nullptr) {
			this->move(movesComponent, spriteComponent, delta);
		}
	}
}


MovesComponent* MovesComponentSystem::addMovesComponent(const TIEntityFactory& factory, TIEntity& entity) {

	MovesComponent* movesComponent = nullptr;
	if (factory.floatValues.count(MovesComponentSystem::SPEED_KEY)) {
		float speed = factory.floatValues.at(MovesComponentSystem::SPEED_KEY);
		movesComponent = entity.addComponent<MovesComponent>();

		sf::Vector2f velocity = sf::Vector2f();
		velocity.x = speed;
		if (factory.floatValues.count(MovesComponentSystem::DIRECTION_KEY)) {
			float direction = factory.floatValues.at(MovesComponentSystem::DIRECTION_KEY);
			velocity.y = direction;
		} else {
			velocity.y = 0;
		}
		movesComponent->setVelocity(velocity);
	}

	return movesComponent;
}

void MovesComponentSystem::setDestination(TIEntity& tientity) {
	MovesComponent* movesComponent = tientity.getComponent<MovesComponent>();
	if (movesComponent != nullptr) {
		sf::Vector2f mousePosition = EventsManager::Instance()->getMouseWorldPosition();
		mousePosition = GridComponentSystem::normalizePositionToGrid(mousePosition);
		movesComponent->setDestination(mousePosition);
	}
};


void MovesComponentSystem::move(MovesComponent* movesComponent, SpriteComponent* spriteComponent, const float delta) {
	if (Math::distanceBetweenTwoPoints(spriteComponent->getPosition(), movesComponent->getDestination()) > 0.5f) {
		if (movesComponent->recalculateVelocity()) {
			movesComponent->setVelocity(sf::Vector2f(movesComponent->getVelocity().x, Math::angleBetweenTwoPoints(spriteComponent->getPosition(), movesComponent->getDestination())));
		}
		spriteComponent->sf::Transformable::move(Math::translateVelocityByTime(movesComponent->getVelocity(), delta));
	} else if (spriteComponent->getPosition() != movesComponent->getDestination()) {
		spriteComponent->setPosition(movesComponent->getDestination());
	}
}

