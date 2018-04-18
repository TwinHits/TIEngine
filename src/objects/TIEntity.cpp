#include "managers/HashManager.h"
#include "managers/LogManager.h"
#include "managers/MessageManager.h"
#include "managers/TimeManager.h"

#include "objects/Message.h"
#include "objects/TIEntity.h"

#include "utilities/MissingSprite.h"

using namespace TIE;

TIEntity::TIEntity() : clock(TimeManager::Instance()->addClock()) {
	this->id = HashManager::Instance()->getNewGlobalId();	
	this->sprite = TIE::getMissingSprite();
}


TIEntity::~TIEntity() {

}


GlobalId TIEntity::getId() const { 
	return this->id;
}


void TIEntity::setDraw(bool b) { 
	this->draw = b;
}


bool TIEntity::getDraw() const { 
	return this->draw; 
}


void TIEntity::setSprite(const sf::Sprite& sprite) {
	this->sprite.setTexture(*sprite.getTexture());
	this->sprite.setTextureRect(sprite.getTextureRect());
	this->sprite.setScale(sprite.getScale());
	this->sprite.setOrigin(sprite.getOrigin());
	this->sprite.setPosition(sprite.getPosition());
}


const sf::Sprite& TIEntity::getSprite() const { 
	return this->sprite;
}


void TIEntity::setDrawOrder(int i) {
	this->drawOrder = i;
}


int TIEntity::getDrawOrder() const {
	return this->drawOrder;
}


void TIEntity::update() {

}


void TIEntity::receiveMessage(const Message& msg) const {

}


bool TIEntity::operator==(const TIEntity& rhs) const {
	return this->getId() == rhs.getId();
}


bool TIEntity::operator!=(const TIEntity& rhs) const {
	return this->getId() != rhs.getId();
}


void TIEntity::operator=(const TIEntity&) {

}
