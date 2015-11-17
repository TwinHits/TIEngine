#include "SceneObject.h"
#include "Message.h"

#include "../managers/TimeManager.h"
#include "../managers/MessageManager.h"
#include "../managers/LogManager.h"
#include "../managers/HashManager.h"

SceneObject::SceneObject()
{
	this->id = HashManager::Instance()->getNewHash();	
	this->clock = TimeManager::Instance()->addClock();
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

void SceneObject::receiveMessage(const Message& msg) {}
void SceneObject::update() {}
