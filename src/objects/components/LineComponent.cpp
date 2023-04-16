#include <SFML/Graphics.hpp>

#include "objects/components/LineComponent.h"

using namespace TIE;

void LineComponent::setMagnitude(const float magnitude) {
    this->magnitude = magnitude;
}


const float LineComponent::getMagnitude() {
    return this->magnitude;
}


const float LineComponent::getMagnitude() const {
    return this->magnitude;
}


void LineComponent::setLine(const sf::VertexArray& line) {
    this->line = line;
}


const sf::VertexArray& LineComponent::getLine() {
    return this->line;
}


const sf::VertexArray& LineComponent::getLine() const {
    return this->line;
}
