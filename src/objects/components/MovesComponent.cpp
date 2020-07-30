#include "objects/components/MovesComponent.h"

using namespace TIE;

void MovesComponent::setVelocity(const sf::Vector2f& velocity) {
	this->velocity = velocity;
};


const sf::Vector2f& MovesComponent::getVelocity() {
	return this->velocity;
}


void MovesComponent::setDestination(const sf::Vector2f& destination) {
	this->destination = destination;
}


const sf::Vector2f& MovesComponent::getDestination() {
	return this->destination;
}

bool MovesComponent::recalculateVelocity() {
	if (this->destination != this->cachedDesintation) {
		this->cachedDesintation = this->destination;
		return true;
	}
	return false;
}
