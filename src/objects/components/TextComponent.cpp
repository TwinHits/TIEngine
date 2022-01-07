#include "objects/components/TextComponent.h"

#include "managers/AssetsManager.h"

using namespace TIE;

TextComponent::TextComponent() {
	const sf::Font& font = TIE::AssetsManager::Instance()->getFont("font.tff");
	this->setString("NO_TEXT");
	this->setFont(font);
	this->setCharacterSize(14);
	this->setPosition(sf::Vector2f(0, 0));
}


void TextComponent::setDrawn(bool drawn) {
	this->drawn = drawn;
}


bool TextComponent::isDrawn() const {
	return this->drawn;
}


const sf::Text& TextComponent::getText() {
	return *dynamic_cast<sf::Text*>(this);
}
