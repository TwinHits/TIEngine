#include "managers/TimeManager.h"
#include "managers/MessageManager.h"
#include "managers/LogManager.h"
#include "managers/HashManager.h"

#include "objects/TIEntity.h"
#include "objects/Message.h"

using namespace TIE;

TIEntity::TIEntity() : clock(TimeManager::Instance()->addClock())
{
	this->id = HashManager::Instance()->getNewGlobalId();	
}

bool TIEntity::operator==(const TIEntity& rhs) const
{
	return this->getId() == rhs.getId();
}

bool TIEntity::operator!=(const TIEntity& rhs) const
{
	return this->getId() != rhs.getId();
}

void TIEntity::setDraw(bool b) { draw = b; }

const sf::Sprite& TIEntity::getSprite() const { return sprite; }
GlobalId TIEntity::getId() const { return id; }
bool TIEntity::getDraw() const { return draw; }

TIEntity::~TIEntity() {}

void TIEntity::operator=(const TIEntity&) {}

void TIEntity::receiveMessage(const Message& msg) const {}
void TIEntity::update() {}
