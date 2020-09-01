#include "objects\components\PositionComponent.h"

using namespace TIE;

void PositionComponent::setPosition(const sf::Vector2f& position) {
    this->position = position;
}

const sf::Vector2f& PositionComponent::getPosition() {
    return this->position;
}

void PositionComponent::setAngle(const float angle) {
    this->angle = angle;
}

float PositionComponent::getAngle() {
    return this->angle;
}
