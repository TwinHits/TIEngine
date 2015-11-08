#include "SceneObject.h"

#include "../managers/TimeManager.h"

SceneObject::SceneObject(unsigned long id)
{
	this->id = id;	
	this->clock = TimeManager::Instance()->addClock();
}

SceneObject::SceneObject(const SceneObject&) {}
SceneObject::~SceneObject() {}
void SceneObject::operator=(const SceneObject&) {}

void SceneObject::setDraw(bool b) { draw = b; }

const sf::Sprite& SceneObject::getSprite() const { return sprite; }
unsigned long SceneObject::getId() const { return id; }

void SceneObject::update()
{
	
}
