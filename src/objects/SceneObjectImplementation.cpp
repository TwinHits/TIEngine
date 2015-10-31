#include "SceneObject.h"

#include "../managers/HashManager.h"

SceneObject::SceneObject()
{
	id = HashManager::Instance()->getNewHash();	
}

SceneObject::SceneObject(const SceneObject&) {}
SceneObject::~SceneObject() {}
void SceneObject::operator=(const SceneObject&) {}

void SceneObject::setDraw(bool b) { draw = b; }

const sf::Sprite& SceneObject::getSprite() { return sprite; }
unsigned long SceneObject::getId() { return id; }

