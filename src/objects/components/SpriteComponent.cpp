#include "objects/components/SpriteComponent.h"

#include "managers/AssetsManager.h"

#include "utils/TIEMath.h"

using namespace TIE;

SpriteComponent::SpriteComponent() {
	sf::Texture& texture = AssetsManager::Instance()->getTexture("missing_texture.png");
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


const sf::Vector2f SpriteComponent::getScaledSize() {
	return sf::Vector2f(this->getTexture()->getSize().x * this->getScale().x, this->getTexture()->getSize().y * this->getScale().y);
}

bool SpriteComponent::isCenterOrigin() {
	return
		TIE::Math::areFloatsEqual(this->getLocalBounds().width / 2, this->getOrigin().x) &&
		TIE::Math::areFloatsEqual(this->getLocalBounds().height / 2, this->getOrigin().y);
}
