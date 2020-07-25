#include "objects/components/GridComponent.h"

using namespace TIE;

const sf::Vector2i& TIE::GridComponent::getGridSize() {
	return this->gridSize;
}


void TIE::GridComponent::setGridSize(const sf::Vector2i& gridSize) {
	this->gridSize = gridSize;
}


const sf::Vector2f& TIE::GridComponent::getTileSize() {
	return this->tileSize;
}


void TIE::GridComponent::setTileSize(const sf::Vector2f& tileSize) {
	this->tileSize = tileSize;
}
