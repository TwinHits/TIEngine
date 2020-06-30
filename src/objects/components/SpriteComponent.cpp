#include "objects/components/SpriteComponent.h"

#include "utilities/MissingSprite.h"

using namespace TIE;

SpriteComponent::SpriteComponent() {
	//Move to get for optimization with a check against sprite.getTexture()
	//this->sprite = getMissingSprite();
}


void SpriteComponent::setDrawn(bool drawn) {
	this->drawn = drawn;
}


bool SpriteComponent::isDrawn() const {
	return this->drawn;
}
