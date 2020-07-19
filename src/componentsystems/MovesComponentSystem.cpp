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
	if (Math::distanceBetweenTwoPoints(spriteComponent->getPosition(), movesComponent->getDestination()) > 0.5f) {
		if (movesComponent->recalculateVelocity()) {
			movesComponent->setVelocity(sf::Vector2f(movesComponent->getVelocity().x, Math::angleBetweenTwoPoints(spriteComponent->getPosition(), movesComponent->getDestination())));
		}
		spriteComponent->sf::Transformable::move(Math::translateVelocityByTime(movesComponent->getVelocity(), delta));
	} else if (spriteComponent->getPosition() != movesComponent->getDestination()) {
		spriteComponent->setPosition(movesComponent->getDestination());
	}
}

