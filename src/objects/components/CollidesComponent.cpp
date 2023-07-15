#include "objects/components/CollidesComponent.h"

#include "objects/GlobalId.h"

using namespace TIE;

void CollidesComponent::setCollidable(bool collidable) {
	this->collidable = collidable;
}


bool CollidesComponent::isCollidable() const {
	return this->collidable;
}


void CollidesComponent::setCollides(bool collides) {
	this->collides = collides;
}


bool CollidesComponent::isCollides() const {
	return this->collides;
}


void CollidesComponent::setPayload(GlobalId payload) {
	this->payload = payload;
}


const GlobalId& CollidesComponent::getPayload() const {
	return this->payload;
}
