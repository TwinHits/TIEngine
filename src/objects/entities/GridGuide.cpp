#include "objects/entities/GridGuide.h"

#include <SFML/Graphics.hpp>

#include "objects/components/ShapeComponent.h"
#include "objects/entities/TIEntity.h"

using namespace TIE;

bool GridGuide::initialize(const sf::FloatRect& bounds, const sf::Vector2i& gridSize, const sf::Vector2f& tileSize) {
	this->setName("GridGuide");
	
	// Y lines
	for (int i = 0; i <= gridSize.x; i++) {
		TIEntity& entity = this->attachChild();
		entity.setName("GridGuide Y " + std::to_string(i));
		ShapeComponent& shapeComponent = entity.addComponent<ShapeComponent>();
		shapeComponent.setDrawn(true);
		sf::RectangleShape rectangleShape = shapeComponent.addRectangleShape();
		rectangleShape.setPosition(sf::Vector2f(bounds.left + tileSize.x * i, bounds.top));
		rectangleShape.setRotation(0); // Why is this different than the rotation guide?
		rectangleShape.setSize(sf::Vector2f(this->GRID_LINE_WIDTH, bounds.height));
		rectangleShape.setFillColor(sf::Color::Yellow);
	}

	// X lines
	 for (int i = 0; i <= gridSize.y; i++) {
		TIEntity& entity = this->attachChild();
		entity.setName("GridGuide X " + std::to_string(i));
		ShapeComponent& shapeComponent = entity.addComponent<ShapeComponent>();
		shapeComponent.setDrawn(true);
		sf::RectangleShape rectangleShape = shapeComponent.addRectangleShape();
		rectangleShape.setPosition(sf::Vector2f(bounds.left, bounds.top + tileSize.y * i));
		rectangleShape.setRotation(270); // Why is this difference than the rotation guide?
		rectangleShape.setSize(sf::Vector2f(this->GRID_LINE_WIDTH, bounds.width));
		rectangleShape.setFillColor(sf::Color::Yellow);
	}

	return true;
}


void GridGuide::update(const float delta) {

}

