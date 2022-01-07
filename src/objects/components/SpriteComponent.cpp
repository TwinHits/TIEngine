#include "objects/components/SpriteComponent.h"

#include "managers/AssetsManager.h"

using namespace TIE;

SpriteComponent::SpriteComponent() {
	sf::Texture& texture = AssetsManager::Instance()->getTexture("missing_texture.png");
	sf::Vector2u size = texture.getSize();
	this->setTexture(texture);
}


void SpriteComponent::setDrawn(bool drawn) {
	this->drawn = drawn;
}


bool SpriteComponent::isDrawn() const {
	return this->drawn;
}

const sf::Sprite& SpriteComponent::getSprite() {
	return *dynamic_cast<sf::Sprite*>(this);
}
