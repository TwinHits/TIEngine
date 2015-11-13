#include "SceneObject.h"

#include "../managers/TimeManager.h"
#include "../managers/MessageManager.h"

SceneObject::SceneObject(unsigned long id)
{
	this->id = id;	
	this->clock = TimeManager::Instance()->addClock();
}

void SceneObject::update()
{
	
}

void SceneObject::receiveMessage(const Message& msg)
{
	switch (msg.value)
	{
		default:
				
			break;
	}	
}

void SceneObject::setDraw(bool b) { draw = b; }

const sf::Sprite& SceneObject::getSprite() const { return sprite; }
unsigned long SceneObject::getId() const { return id; }

SceneObject::~SceneObject() {}
