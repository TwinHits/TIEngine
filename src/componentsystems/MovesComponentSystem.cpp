#include "componentsystems/MovesComponentSystem.h" 

#include <cmath>

#include <SFML/Graphics.hpp>

#include "managers/LogManager.h" 
#include "objects/components/MovesComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "utilities/TIEMath.h"

using namespace TIE;

void MovesComponentSystem::update(TIEntity& entity, const float delta) {
	MovesComponent* movesComponent = entity.getComponent<MovesComponent>();
	if (movesComponent != nullptr) {
		SpriteComponent* spriteComponent = entity.getComponent<SpriteComponent>();
		if (spriteComponent != nullptr) {
			this->move(movesComponent, spriteComponent, delta);
		}
	}
}


void MovesComponentSystem::move(MovesComponent* movesComponent, SpriteComponent* spriteComponent, const float delta) {
	if (Math::distanceBetweenTwoPoints(spriteComponent->getPosition(), movesComponent->getDestination()) > 0.25f) {
		sf::Vector2f velocity = movesComponent->getVelocity();
		velocity.y = Math::angleBetweenTwoPoints(spriteComponent->getPosition(), movesComponent->getDestination());
		movesComponent->setVelocity(velocity);
		spriteComponent->sf::Transformable::move(Math::translateVelocityByTime(velocity, delta));
	}
}

