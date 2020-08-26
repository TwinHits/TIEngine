#include "objects/components/MovesComponent.h"

using namespace TIE;

void MovesComponent::setVelocity(const sf::Vector2f& velocity) {
	this->velocity = velocity;
};


sf::Vector2f& MovesComponent::getVelocity() {
	return this->velocity;
}


void MovesComponent::setTargetPosition(const sf::Vector2f& targetPosition) {
	this->targetPosition = targetPosition;
}


sf::Vector2f& MovesComponent::getTargetPosition() {
	return this->targetPosition;
}


void MovesComponent::setAngularVelocity(const sf::Vector2f& angularVelocity) {
	this->angularVelocity = angularVelocity;
}


sf::Vector2f& MovesComponent::getAngularVelocity() {
	return this->angularVelocity;
}


void MovesComponent::setTargetAngle(const float targetAngle) {
	this->targetAngle = targetAngle;
}


float MovesComponent::getTargetAngle() {
	return this->targetAngle;
}

