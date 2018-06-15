#include "managers/TimeManager.h"
#include "managers/LogManager.h"
#include "managers/HashManager.h"

#include "objects/drawables/SceneText.h"

#include "utilities/GetMissingText.h"


using namespace TIE;

SceneText::SceneText() {
	this->id = HashManager::Instance()->getNewGlobalId();	
	this->text = TIE::getMissingText();
}


SceneText::~SceneText() {
	
}


GlobalId SceneText::getId() const { 
	return id;
}


void SceneText::setText(const sf::Text& text) {
	this->text.setString(text.getString());
	this->text.setFont(*text.getFont());
	this->text.setCharacterSize(text.getCharacterSize());
	this->text.setPosition(text.getPosition());
}


sf::Text& SceneText::getText() {
	return text; 
}


const sf::Text& SceneText::getText() const { 
	return text; 
}


void SceneText::setDraw(bool b) { 
	draw = b; 
}


bool SceneText::getDraw() const { 
	return draw; 
}


void SceneText::update(const float delta) {

}


bool SceneText::operator==(const SceneText& rhs) const {
	return this->getId() == rhs.getId();
}


bool SceneText::operator!=(const SceneText& rhs) const {
	return this->getId() != rhs.getId();
}


void SceneText::operator=(const SceneText&) {

}
