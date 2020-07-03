#include "managers/AssetsManager.h"

#include "objects/components/SpriteComponent.h"

using namespace TIE;

SpriteComponent::SpriteComponent() {
	sf::Texture& texture = AssetsManager::Instance()->getTexture("missing_texture.png");
	sf::Vector2u size = texture.getSize();
	this->setTexture(texture);
	this->setOrigin(size.x/4, size.y/4); //No idea why it's /4
}


void SpriteComponent::setDrawn(bool drawn) {
	this->drawn = drawn;
}


bool SpriteComponent::isDrawn() const {
	return this->drawn;
}
