#include "objects/components/ShapeComponent.h"

using namespace TIE;

void ShapeComponent::setDrawn(bool drawn) {
	this->drawn = drawn;
}


bool ShapeComponent::isDrawn() const {
	return this->drawn;
}


const sf::Shape& ShapeComponent::getShape() {
	return *dynamic_cast<sf::Shape*>(this);
}