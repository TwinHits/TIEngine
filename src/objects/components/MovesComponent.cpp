#include "objects/components/MovesComponent.h"

using namespace TIE;

void MovesComponent::setVelocity(sf::Vector2f velocity) {
	this->velocity = velocity;
};

const sf::Vector2f MovesComponent::getVelocity() {
	return this->velocity;
};
