#include "SceneObject.h"
#include "Message.h"

#include "../managers/TimeManager.h"
#include "../managers/MessageManager.h"
#include "../managers/LogManager.h"

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
	if (msg.receiver == *this)
	{
		switch (msg.type)
		{
			case Message::Move:
					LogManager::Instance()->logInfo("Sucessful message receieved");
				break;
			default:
				break;
		}
	}
}
void SceneObject::action(const SceneObject& target)
{
	Message msg(*this, target);
	msg.type = Message::Move;
	MessageManager::Instance()->sendMessage(msg);
}

bool SceneObject::operator==(const SceneObject& rhs) const 
{
	return this->getId() == rhs.getId();
}

bool SceneObject::operator!=(const SceneObject& rhs) const
{
	return this->getId() != rhs.getId();
}

void SceneObject::setDraw(bool b) { draw = b; }

const sf::Sprite& SceneObject::getSprite() const { return sprite; }
unsigned long SceneObject::getId() const { return id; }
bool SceneObject::getDraw() { return draw; }

SceneObject::~SceneObject() {}

void SceneObject::operator=(const SceneObject&) {}
