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


void MovesComponent::setCachedTargetPosition(const sf::Vector2f& cachedTargetPosition) {
	this->cachedTargetPosition = cachedTargetPosition;
}


const sf::Vector2f& MovesComponent::getCachedTargetPosition() const {
	return this->cachedTargetPosition;
}


void MovesComponent::setAngularVelocity(const sf::Vector2f& angularVelocity) {
	this->angularVelocity = angularVelocity;
}


const sf::Vector2f& MovesComponent::getAngularVelocity() const {
	return this->angularVelocity;
}


void MovesComponent::setTargetAngle(const float targetAngle) {
	this->targetAngle = targetAngle;
}


const float MovesComponent::getTargetAngle() const {
	return this->targetAngle;
}


void MovesComponent::setCachedTargetAngle(const float cachedTargetAngle) {
	this->cachedTargetAngle = cachedTargetAngle;
}


const float MovesComponent::getCachedTargetAngle() const {
	return this->cachedTargetAngle;
}

