#include "objects/components/TextComponent.h"

#include "componentsystems/TextComponentSystem.h"
#include "managers/AssetsManager.h"
#include "objects/assets/FontAsset.h"
#include "objects/enumeration/TextAlignment.h"

using namespace TIE;

TextComponent::TextComponent() {
	const FontAsset& font = AssetsManager::Instance()->getFont(TextComponentSystem::FONT_DEFAULT);
	this->setFont(font);
	this->setCharacterSize(14);
	this->setString("NO_TEXT");
	this->setPosition(sf::Vector2f(0, 0));
	this->setTextAlignment(TextAlignment::TOP_LEFT);
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


void TextComponent::setFont(const FontAsset& fontAsset) {
	this->fontAsset = &fontAsset;
	this->sf::Text::setFont(fontAsset);
}


const FontAsset& TextComponent::getFont() {
	return *this->fontAsset;
}


const FontAsset& TextComponent::getFont() const {
	return *this->fontAsset;
}


const sf::Text& TextComponent::getText() {
	return *dynamic_cast<sf::Text*>(this);
}
