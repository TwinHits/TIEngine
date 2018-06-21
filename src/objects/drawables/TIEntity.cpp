#include "managers/HashManager.h"
#include "managers/LogManager.h"
#include "managers/TimeManager.h"

#include "objects/drawables/TIEntity.h"

#include "utilities/GetMissingSprite.h"
#include "utilities/ToRadians.h"

using namespace TIE;

TIEntity::TIEntity() {
	this->sprite = TIE::getMissingSprite();
}


TIEntity::~TIEntity() {

}


void TIEntity::setCollidable(bool b) { 
	this->collidable = b;
}


bool TIEntity::getCollidable() { 
	return this->collidable; 
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


void TIEntity::setAngle(float angle) {
	this->sprite.setRotation(angle);
}


float TIEntity::getAngle() {
	return this->sprite.getRotation();
}


void TIEntity::setSpeed(float speed) {
	this->speed = speed;
}


float TIEntity::getSpeed() {
	return this->speed;
}


void TIEntity::move(const float delta) {
	float degrees = sprite.getRotation();
	float x = 0;
	float y = 0;

	//Handle special values because of sin/cos handling the seminal values
	if (degrees == 0.0) {
		x = std::cos(ToRadians(degrees)) * speed * delta;
	} else if (degrees == 90.0) {
		y = std::sin(ToRadians(degrees)) * speed * delta;
	} else if (degrees == 180.0) {
		x = std::cos(ToRadians(degrees)) * speed * delta;
	} else if (degrees == 270.0) {
		y = std::sin(ToRadians(degrees)) * speed * delta;
	} else {
		x = std::cos(ToRadians(degrees)) * speed * delta;
		y = std::sin(ToRadians(degrees)) * speed * delta;
	}

    sprite.move(sf::Vector2f(x, y));
}


void TIEntity::drawSelf(sf::RenderWindow& window, sf::RenderStates states) const {
	
}


void TIEntity::updateSelf(const float delta) {
	
}


bool TIEntity::operator==(const TIEntity& rhs) const {
	return this->getId() == rhs.getId();
}


bool TIEntity::operator!=(const TIEntity& rhs) const {
	return this->getId() != rhs.getId();
}


void TIEntity::operator=(const TIEntity&) {

}
