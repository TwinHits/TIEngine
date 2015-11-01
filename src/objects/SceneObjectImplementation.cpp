#include "SceneObject.h"

SceneObject::SceneObject(unsigned long id)
{
	this->id = id;	
}

SceneObject::SceneObject(const SceneObject&) {}
SceneObject::~SceneObject() {}
void SceneObject::operator=(const SceneObject&) {}

void SceneObject::setDraw(bool b) { draw = b; }

const sf::Sprite& SceneObject::getSprite() const { return sprite; }
unsigned long SceneObject::getId() const { return id; }

