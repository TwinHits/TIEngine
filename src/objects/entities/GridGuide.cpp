#include "objects/entities/GridGuide.h"

#include <SFML/Graphics.hpp>

#include "objects/components/ShapeComponent.h"
#include "objects/entities/TIEntity.h"

using namespace TIE;

bool GridGuide::initialize(const sf::FloatRect& bounds, const sf::Vector2i& gridSize, const sf::Vector2f& tileSize) {
	
	// Y lines
	for (int i = 0; i <= gridSize.x; i++) {
		TIEntity& entity = this->attachChild();
		ShapeComponent& shape = entity.addComponent<ShapeComponent>();
		shape.setDrawn(true);
		shape.setPosition(sf::Vector2f(bounds.left + tileSize.x * i, bounds.top));
		shape.setRotation(0); // Why is this different than the rotation guide?
		shape.setSize(sf::Vector2f(this->GRID_LINE_WIDTH, bounds.height));
		shape.setFillColor(sf::Color::Yellow);
	}

	// X lines
	 for (int i = 0; i <= gridSize.y; i++) {
		TIEntity& entity = this->attachChild();
		ShapeComponent& shape = entity.addComponent<ShapeComponent>();
		shape.setDrawn(true);
		shape.setPosition(sf::Vector2f(bounds.left, bounds.top + tileSize.y * i));
		shape.setRotation(270); // Why is this difference than the rotation guide?
		shape.setSize(sf::Vector2f(this->GRID_LINE_WIDTH, bounds.width));
		shape.setFillColor(sf::Color::Yellow);
	}

	return true;
}


void GridGuide::update(const float delta) {

}

