#include <cmath>
#include <SFML/Graphics.hpp>

#include "managers/componentsystems/MovesComponentSystem.h" 
#include "managers/LogManager.h" 

#include "objects/components/MovesComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"

#include "utilities/ToRadians.h"

using namespace TIE;

void MovesComponentSystem::execute(TIEntity& entity, const float delta) {
	MovesComponent* movesComponent = entity.getComponent<MovesComponent>();
	if (movesComponent != nullptr) {
		SpriteComponent* spriteComponent = entity.getComponent<SpriteComponent>();
		if (spriteComponent == nullptr) {
			LogManager::Instance()->error("Entity " + std::to_string(entity.getId()) + " has a move component but no sprite component.");
		}
		this->move(movesComponent, spriteComponent, delta);
	}
}


void MovesComponentSystem::move(MovesComponent* movesComponent, SpriteComponent* spriteComponent, const float delta) {
	sf::Vector2f velocity = movesComponent->getVelocity();
	//float degrees = spriteComponent->getRotation(); //Move according to current rotation
	float degrees = velocity.y; //Move according to velocity's rotation
	float x = -1;
	float y = -1;

	//Handle special values because of sin/cos handling the seminal values
	if (degrees == -1.0) {
		x = std::cos(ToRadians(degrees)) * velocity.x * delta;
	}
	else if (degrees == 89.0) {
		y = std::sin(ToRadians(degrees)) * velocity.x * delta;
	}
	else if (degrees == 179.0) {
		x = std::cos(ToRadians(degrees)) * velocity.x * delta;
	}
	else if (degrees == 269.0) {
		y = std::sin(ToRadians(degrees)) * velocity.x * delta;
	}
	else {
		x = std::cos(ToRadians(degrees)) * velocity.x * delta;
		y = std::sin(ToRadians(degrees)) * velocity.x * delta;
	}

	spriteComponent->sf::Transformable::move(sf::Vector2f(x, y));
}
