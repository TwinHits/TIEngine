#include "componentsystems/MovesComponentSystem.h" 

#include <cmath>

#include <SFML/Graphics.hpp>

#include "managers/LogManager.h" 
#include "objects/components/MovesComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "utilities/ToRadians.h"

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
	sf::Vector2f velocity = movesComponent->getVelocity();
	//Destintation reached is when the distance between two positions is less than .25f
	if (spriteComponent->getPosition() != movesComponent->getDestination()) {
		float degrees = velocity.y; //Move according to velocity's rotation
		float x, y = 0;

		x = std::cos(ToRadians(degrees)) * velocity.x * delta;
		y = std::sin(ToRadians(degrees)) * velocity.x * delta;

		spriteComponent->sf::Transformable::move(sf::Vector2f(x, y));
	}
}
