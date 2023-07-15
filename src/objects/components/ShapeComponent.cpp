#include "objects/components/ShapeComponent.h"

#include <vector>

#include <SFML/Graphics.hpp>

#include "objects/GlobalId.h"
#include "managers/HashManager.h"
#include "templates/MakeUnique.h"

using namespace TIE;

void ShapeComponent::setDrawn(bool drawn) {
	this->drawn = drawn;
}


bool ShapeComponent::isDrawn() const {
	return this->drawn;
}


void ShapeComponent::setRotates(const bool rotates) {
	this->rotates = rotates;
}


const bool ShapeComponent::isRotates() const {
	return this->rotates;
}


sf::RectangleShape& ShapeComponent::addRectangleShape() {
	const GlobalId id = HashManager::Instance()->getNewGlobalId();
	return this->addRectangleShape(id);
}


sf::RectangleShape& ShapeComponent::addRectangleShape(const GlobalId id) {
	this->shapes[id] = TIE::make_unique<sf::RectangleShape>();
	return dynamic_cast<sf::RectangleShape&>(*this->shapes.at(id));
}


sf::CircleShape& ShapeComponent::addCircleShape() {
	const GlobalId id = HashManager::Instance()->getNewGlobalId();
	return this->addCircleShape(id);
}


sf::CircleShape& ShapeComponent::addCircleShape(const GlobalId id) {
	this->shapes[id] = TIE::make_unique<sf::CircleShape>();
	return dynamic_cast<sf::CircleShape&>(*this->shapes.at(id));
}


const std::map<GlobalId, std::unique_ptr<sf::Shape> >& ShapeComponent::getShapes() {
	return this->shapes;
}


const std::map<GlobalId, std::unique_ptr<sf::Shape> >& ShapeComponent::getShapes() const {
	return this->shapes;
}


sf::Shape* ShapeComponent::getShape(const GlobalId id) {
	if (this->shapes.count(id)) {
		return this->shapes[id].get();
	} else {
		return nullptr;
	}
}
