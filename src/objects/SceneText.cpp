#include "managers/TimeManager.h"
#include "managers/MessageManager.h"
#include "managers/LogManager.h"
#include "managers/HashManager.h"

#include "objects/SceneText.h"
#include "objects/Message.h"

using namespace TIE;

SceneText::SceneText() : clock(TimeManager::Instance()->addClock())
{
	this->id = HashManager::Instance()->getNewGlobalId();	
}

bool SceneText::operator==(const SceneText& rhs) const
{
	return this->getId() == rhs.getId();
}

bool SceneText::operator!=(const SceneText& rhs) const
{
	return this->getId() != rhs.getId();
}

void SceneText::setDraw(bool b) { draw = b; }

sf::Text& SceneText::getText() { return text; }
const sf::Text& SceneText::getText() const { return text; }
GlobalId SceneText::getId() const { return id; }
bool SceneText::getDraw() const { return draw; }

SceneText::~SceneText() {}

void SceneText::operator=(const SceneText&) {}

void SceneText::receiveMessage(const Message& msg) const {}
void SceneText::update() {}
