#include "managers/TimeManager.h"
#include "managers/MessageManager.h"
#include "managers/LogManager.h"
#include "managers/HashManager.h"

#include "objects/SceneObject.h"
#include "objects/Message.h"

using namespace TIE;

SceneObject::SceneObject() : clock(TimeManager::Instance()->addClock())
{
	this->id = HashManager::Instance()->getNewGlobalId();	
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
GlobalId SceneObject::getId() const { return id; }
bool SceneObject::getDraw() const { return draw; }

SceneObject::~SceneObject() {}

void SceneObject::operator=(const SceneObject&) {}

void SceneObject::receiveMessage(const Message& msg) const {}
void SceneObject::update() {}
