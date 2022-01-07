#include "objects/components/SpriteComponent.h"

#include "managers/AssetsManager.h"

using namespace TIE;

SpriteComponent::SpriteComponent() {
	sf::Texture& texture = AssetsManager::Instance()->getTexture("missing_texture.png");
	sf::Vector2u size = texture.getSize();
	bool rotates = true;
	this->setTexture(texture);
}


void SpriteComponent::setDrawn(bool drawn) {
	this->drawn = drawn;
}


bool SpriteComponent::isDrawn() const {
	return this->drawn;
}


void SpriteComponent::setRotates(bool rotates) {
	this->rotates = rotates;
}


bool SpriteComponent::isRotates() const {
	return this->rotates;
}


const sf::Sprite& SpriteComponent::getSprite() {
	return *dynamic_cast<sf::Sprite*>(this);
}
