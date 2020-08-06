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


const sf::Vector2f& MovesComponent::getDestination() const {
	return this->destination;
}


void MovesComponent::setCachedDestination(const sf::Vector2f& cachedDestination) {
	this->cachedDesintation = cachedDestination;
}


const sf::Vector2f& MovesComponent::getCachedDestination() const {
	return this->cachedDesintation;
}

