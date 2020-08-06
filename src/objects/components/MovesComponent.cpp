#include "objects/components/MovesComponent.h"

using namespace TIE;

void MovesComponent::setVelocity(const sf::Vector2f& velocity) {
	this->velocity = velocity;
};


const sf::Vector2f& MovesComponent::getVelocity() {
	return this->velocity;
}


void MovesComponent::setTargetPosition(const sf::Vector2f& targetPosition) {
	this->targetPosition = targetPosition;
}


const sf::Vector2f& MovesComponent::getTargetPosition() const {
	return this->targetPosition;
}


void MovesComponent::setCachedTargetPosition(const sf::Vector2f& cachedTargetDestination) {
	this->cachedTargetPosition = cachedTargetDestination;
}


const sf::Vector2f& MovesComponent::getCachedTargetPosition() const {
	return this->cachedTargetPosition;
}

