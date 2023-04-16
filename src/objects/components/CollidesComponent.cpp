#include "objects/components/CollidesComponent.h"

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
