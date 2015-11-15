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
	switch (msg.type)
	{
		case Message::Move:
			break;
		default:
			break;
	}
}

void SceneObject::action()
{
	Message msg(*this, *this);
	msg.type = Message::Move;
	MessageManager::Instance()->sendMessage(msg);
}

void SceneObject::setDraw(bool b) { draw = b; }

const sf::Sprite& SceneObject::getSprite() const { return sprite; }
unsigned long SceneObject::getId() const { return id; }
bool SceneObject::getDraw() { return draw; }

SceneObject::~SceneObject() {}
SceneObject::SceneObject(const SceneObject&) {}

