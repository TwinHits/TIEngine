#include "objects/entities/GridGuide.h"

#include <SFML/Graphics.hpp>

#include "objects/components/ShapeComponent.h"
#include "objects/entities/TIEntity.h"

using namespace TIE;

bool GridGuide::initialize(const sf::Vector2f& position, const sf::Vector2i& gridSize, const sf::Vector2f& tileSize) {

	int GRID_LINE_WIDTH = 2;
	float totalWidth = tileSize.x * gridSize.x;
	float totalHeight = tileSize.y * gridSize.y;
	sf::Vector2f normalizedPosition = sf::Vector2f(position.x - totalWidth / 2, position.y - totalHeight / 2);
	
	// Y lines
	for (int i = 0; i < gridSize.x; i++) {
		TIEntity& entity = this->attachChild();
		ShapeComponent* shape = entity.addComponent<ShapeComponent>();
		shape->setDrawn(true);
		shape->setPosition(sf::Vector2f(normalizedPosition.x + tileSize.x * i, normalizedPosition.y));
		shape->setRotation(0); // Why is this different than the rotation guide?
		shape->setSize(sf::Vector2f(GRID_LINE_WIDTH, totalHeight));
		shape->setFillColor(sf::Color::Yellow);
	}

	// X lines
	 for (int i = 0; i < gridSize.y; i++) {
		TIEntity& entity = this->attachChild();
		ShapeComponent* shape = entity.addComponent<ShapeComponent>();
		shape->setDrawn(true);
		shape->setPosition(sf::Vector2f(normalizedPosition.x, normalizedPosition.y + tileSize.y * i));
		shape->setRotation(270); // Why is this difference than the rotation guide?
		shape->setSize(sf::Vector2f(GRID_LINE_WIDTH, totalWidth));
		shape->setFillColor(sf::Color::Yellow);
	}

	return true;
}


void GridGuide::update(const float delta) {

}

