#include "objects/components/TextComponent.h"

#include "componentsystems/TextComponentSystem.h"
#include "managers/AssetsManager.h"
#include "objects/enumeration/TextAlignment.h"

using namespace TIE;

TextComponent::TextComponent() {
	const sf::Font& font = TIE::AssetsManager::Instance()->getFont("font.tff");
	this->setFont(font);
	this->setCharacterSize(14);
	this->setString("NO_TEXT");
	this->setPosition(sf::Vector2f(0, 0));
	this->setTextAlignment(TextAlignment::LEFT);
}


void TextComponent::setString(const std::string& string) {
	this->sf::Text::setString(string);
	TextComponentSystem::setOriginForTextAlignment(*this);
}


void TextComponent::setDrawn(bool drawn) {
	this->drawn = drawn;
}


bool TextComponent::isDrawn() const {
	return this->drawn;
}


void TextComponent::setTextAlignment(TextAlignment textAlignment) {
	this->textAlignment = textAlignment;
	TextComponentSystem::setOriginForTextAlignment(*this);
}


TextAlignment TextComponent::getTextAlignment() const {
	return this->textAlignment;
}


const sf::Text& TextComponent::getText() {
	return *dynamic_cast<sf::Text*>(this);
}
