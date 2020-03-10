#include "managers/TimeManager.h"
#include "managers/LogManager.h"
#include "managers/HashManager.h"

#include "objects/drawables/TIExt.h"

#include "utilities/GetMissingText.h"


using namespace TIE;

TIExt::TIExt() {
	this->text = getMissingText();
	this->setType("TIExt");
}


TIExt::~TIExt() {
	
}


void TIExt::setText(const sf::Text& text) {
	this->text.setString(text.getString());
	this->text.setFont(*text.getFont());
	this->text.setCharacterSize(text.getCharacterSize());
	this->text.setPosition(text.getPosition());
}


void TIExt::setTextString(const std::string& string) {
	this->text.setString(string);
}


sf::Text& TIExt::getText() {
	return this->text; 
}


const sf::Text& TIExt::getText() const { 
	return this->text; 
}


void TIExt::updateSelf(const float delta) {

}

void TIExt::drawSelf(sf::RenderTarget& window, sf::RenderStates states) const {
	window.draw(this->text, states);
}


bool TIExt::operator==(const TIExt& rhs) const {
	return this->getId() == rhs.getId();
}


bool TIExt::operator!=(const TIExt& rhs) const {
	return this->getId() != rhs.getId();
}


void TIExt::operator=(const TIExt&) {

}
