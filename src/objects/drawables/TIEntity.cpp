#include "managers/HashManager.h"
#include "managers/LogManager.h"
#include "managers/TimeManager.h"

#include "objects/drawables/TIEntity.h"

#include "utilities/GetMissingSprite.h"
#include "utilities/ToRadians.h"

using namespace TIE;

TIEntity::TIEntity() {
	this->sprite = TIE::getMissingSprite();
	this->setType("TIEntity.");
}


TIEntity::~TIEntity() {

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


void TIEntity::setVelocity(sf::Vector2f velocity) {
	this->velocity = velocity;
}


const sf::Vector2f TIEntity::getVelocity() {
	return this->velocity;
}


sf::FloatRect TIEntity::getHitBox() const {
	return this->getWorldTransform().transformRect(this->sprite.getGlobalBounds());
}


void TIEntity::move(const float delta) {
	float degrees = this->getRotation();
	float x = 0;
	float y = 0;

	//Handle special values because of sin/cos handling the seminal values
	if (degrees == 0.0) {
		x = std::cos(ToRadians(degrees)) * this->velocity.x * delta;
	} else if (degrees == 90.0) {
		y = std::sin(ToRadians(degrees)) * this->velocity.x * delta;
	} else if (degrees == 180.0) {
		x = std::cos(ToRadians(degrees)) * this->velocity.x * delta;
	} else if (degrees == 270.0) {
		y = std::sin(ToRadians(degrees)) * this->velocity.x * delta;
	} else {
		x = std::cos(ToRadians(degrees)) * this->velocity.x * delta;
		y = std::sin(ToRadians(degrees)) * this->velocity.x * delta;
	}

    this->sf::Transformable::move(sf::Vector2f(x, y));
}


void TIEntity::drawSelf(sf::RenderTarget& window, sf::RenderStates states) const {
	window.draw(sprite, states);	
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
