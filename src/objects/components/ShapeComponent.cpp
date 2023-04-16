#include "objects/components/ShapeComponent.h"

#include <vector>

#include <SFML/Graphics.hpp>

#include <templates/MakeUnique.h>

using namespace TIE;

void ShapeComponent::setDrawn(bool drawn) {
	this->drawn = drawn;
}


bool ShapeComponent::isDrawn() const {
	return this->drawn;
}


sf::RectangleShape& ShapeComponent::addRectangleShape() {
	this->shapes.push_back(TIE::make_unique<sf::RectangleShape>());
	return dynamic_cast<sf::RectangleShape&>(*this->shapes.back());
}


sf::CircleShape& ShapeComponent::addCircleShape() {
	this->shapes.push_back(TIE::make_unique<sf::CircleShape>());
	return dynamic_cast<sf::CircleShape&>(*this->shapes.back());
}


const std::vector<std::unique_ptr<sf::Shape> >& ShapeComponent::getShapes() {
	return this->shapes;
}

const std::vector<std::unique_ptr<sf::Shape> >& ShapeComponent::getShapes() const {
	return this->shapes;
}
