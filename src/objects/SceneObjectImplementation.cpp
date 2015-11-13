#include <iostream>

#include "SceneObject.h"
#include "Message.h"

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
		case 123:
			if (this->id == 4)
				std::cout << "success!" << std::endl;
		default:
			break;
	}
}

void SceneObject::action()
{
	Message msg;
	msg.value = 123;
	MessageManager::Instance()->sendMessage(msg);
}

void SceneObject::setDraw(bool b) { draw = b; }

const sf::Sprite& SceneObject::getSprite() const { return sprite; }
unsigned long SceneObject::getId() const { return id; }

SceneObject::~SceneObject() {}
SceneObject::SceneObject(const SceneObject&) {}

