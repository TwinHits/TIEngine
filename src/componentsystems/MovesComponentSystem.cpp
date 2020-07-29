#include "componentsystems/MovesComponentSystem.h" 

#include <cmath>
#include <string>

#include <SFML/Graphics.hpp>

#include "managers/LogManager.h" 
#include "objects/components/MovesComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"
#include "utilities/TIEMath.h"

using namespace TIE;

const std::string MovesComponentSystem::MOVES = "moves";
const std::string MovesComponentSystem::SPEED = "speed";
const std::string MovesComponentSystem::DIRECTION = "direction";

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
	auto speed = factory.floatValues.find("moves.speed");
	auto direction = factory.floatValues.find("moves.direction");
	
	if (speed != factory.floatValues.end()) {
		MovesComponent* movesComponent = entity.addComponent<MovesComponent>();

		sf::Vector2f velocity = sf::Vector2f();
		velocity.x = speed->second;
		if (direction != factory.floatValues.end()) {
			velocity.y = direction->second;
		} else {
			velocity.y = 0;
		}
		movesComponent->setVelocity(velocity);
	}

	return movesComponent;
}


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

