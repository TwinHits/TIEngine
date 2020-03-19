#include <SFML/Graphics.hpp>

#include "managers/AssetsManager.h"

#include "utilities/MissingSprite.h"

sf::Sprite TIE::getMissingSprite() {
	sf::Sprite sprite;

	sprite.setTexture(TIE::AssetsManager::Instance()->getTexture("missing_texture.png"));
	sprite.setTextureRect(sf::IntRect(0, 0, 32, 48));
	sprite.setScale(2, 2);
	sprite.setOrigin(16, 48);
	sprite.setPosition(0, 0);

	return sprite;
}
