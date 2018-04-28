#include "managers/HashManager.h"
#include "managers/LogManager.h"
#include "managers/MessageManager.h"
#include "managers/TimeManager.h"

#include "objects/Message.h"
#include "objects/TIEntity.h"

#include "utilities/MissingSprite.h"
#include "utilities/ToDegrees.h"

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


void TIEntity::setSpeed(double speed) {
	this->speed = speed;
}


double TIEntity::getSpeed() const {
	return this->speed;
}


void TIEntity::update() {

}


void TIEntity::receiveMessage(const Message& msg) const {

}

void TIEntity::move(const sf::Vector2f destination, const float delta) {
	/**
	Get the cartesian coordinates. Make Y positions negative because screen
	coordainates are as if they are in quadrant 4.
	**/
	auto position = sprite.getPosition();
	double x = destination.x - position.x;
	double y = destination.y - position.y;

	//Convert to polar vector.
	double magnitude = std::hypot(x, y);
	double direction = std::atan(y / x);

	//C++'s inverse tangent function returns radians, convert to degrees
	direction = ToDegrees(direction);

	//Add or subtrack according to quadrant
	if (y >= 0 && x >= 0)
		direction = direction;
	else if (x < 0 && y < 0)
		direction = direction + 360;
	else
		direction = direction + 180;

	//Normalize distances. Not sure why.
	double normalX = x / magnitude;
	double normalY = y / magnitude;

	//Move along this direction per speed of this object for the time since last calcuation
	auto yMove = normalY * this->speed * delta;
	auto xMove = normalX * this->speed * delta;

	//Actually move the sprite
	sprite.move(sf::Vector2f(xMove, yMove));

}


bool TIEntity::operator==(const TIEntity& rhs) const {
	return this->getId() == rhs.getId();
}


bool TIEntity::operator!=(const TIEntity& rhs) const {
	return this->getId() != rhs.getId();
}


void TIEntity::operator=(const TIEntity&) {

}
