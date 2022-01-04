#include "interfaces/TIEntityInterface.h"

#include "sol/sol.hpp"

#include "componentsystems/BehaviorComponentSystem.h"
#include "componentsystems/CacheComponentSystem.h"
#include "componentsystems/MovesComponentSystem.h"
#include "componentsystems/EventsComponentSystem.h"
#include "interfaces/Vector2Interface.h"
#include "managers/LogManager.h"
#include "managers/WorldManager.h"
#include "objects/GlobalId.h"
#include "objects/components/MovesComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/components/structs/EventState.h"
#include "objects/enumeration/Direction.h"
#include "utils/ComponentSystems.h"

using namespace TIE;

TIEntityInterface::TIEntityInterface(TIEntity& tientity) {
    this->tientity = &tientity;
}


TIEntityInterface::TIEntityInterface(TIEntity* tientity) {
    this->tientity = tientity;
}


void TIEntityInterface::registerUserType(sol::state& luaState) {
    sol::usertype<TIEntityInterface> interfaceUserType = luaState.new_usertype<TIEntityInterface>("tientity");
    interfaceUserType["getId"] = &TIEntityInterface::getId;
    interfaceUserType["spawn"] = &TIEntityInterface::spawn;
    interfaceUserType["despawn"] = &TIEntityInterface::despawn;
    interfaceUserType["setDrawn"] = &TIEntityInterface::setDrawn;
	interfaceUserType["getPosition"] = &TIEntityInterface::getPosition;
	interfaceUserType["setPosition"] = &TIEntityInterface::setPosition;
	interfaceUserType["setDestination"] = &TIEntityInterface::setDestination;
	interfaceUserType["atDestination"] = &TIEntityInterface::atDestination;
    interfaceUserType["moveRight"] = &TIEntityInterface::moveRight;
    interfaceUserType["moveLeft"] = &TIEntityInterface::moveLeft;
    interfaceUserType["moveUp"] = &TIEntityInterface::moveUp;
    interfaceUserType["moveDown"] = &TIEntityInterface::moveDown;
    interfaceUserType["addState"] = &TIEntityInterface::addState;
    interfaceUserType["removeState"] = &TIEntityInterface::removeState;
    interfaceUserType["getState"] = &TIEntityInterface::getState;
    interfaceUserType["setCache"] = &TIEntityInterface::setCache;
    interfaceUserType["getCache"] = &TIEntityInterface::getCache;
    interfaceUserType["setBehaviorById"] = &TIEntityInterface::setBehaviorById;
    interfaceUserType["setBehaviorByName"] = &TIEntityInterface::setBehaviorByName;
}


GlobalId TIEntityInterface::getId() {
    return this->tientity->getId();
}


void TIEntityInterface::spawn(const std::string& entityName) {
    WorldManager::Instance()->spawnTIEntity(entityName);
}


void TIEntityInterface::despawn() {
    this->setDrawn(false);
}


void TIEntityInterface::setDrawn(bool drawn) {
    ComponentSystems::setDrawn(*this->tientity, drawn);
}


Vector2fInterface TIEntityInterface::getPosition() {
    PositionComponent* positionComponent = this->tientity->getComponent<PositionComponent>();
    if (positionComponent != nullptr) {
        return Vector2fInterface(positionComponent->position.x, positionComponent->position.y);
    } else {
        return Vector2fInterface(0.0F, 0.0F);
    }
}


void TIEntityInterface::setPosition(const float x, const float y) {
    PositionComponent* positionComponent = this->tientity->getComponent<PositionComponent>();
    if (positionComponent != nullptr) {
        sf::Vector2f newPosition = sf::Vector2f(x, y);
        positionComponent->position = newPosition;
    }
}


void TIEntityInterface::setDestination(const float x, const float y) {
    MovesComponentSystem::Instance()->setTargetPosition(*this->tientity, sf::Vector2f(x, y));
}


bool TIEntityInterface::atDestination() {
    return MovesComponentSystem::Instance()->atTargetPosition(*this->tientity);
}


void TIEntityInterface::moveUp() {
    MovesComponentSystem::Instance()->setTargetPosition(*this->tientity, Direction::TOP);
}


void TIEntityInterface::moveRight() {
    MovesComponentSystem::Instance()->setTargetPosition(*this->tientity, Direction::RIGHT);
}


void TIEntityInterface::moveLeft() {
    MovesComponentSystem::Instance()->setTargetPosition(*this->tientity, Direction::LEFT);
}


void TIEntityInterface::moveDown() {
    MovesComponentSystem::Instance()->setTargetPosition(*this->tientity, Direction::BOTTOM);
}


void TIEntityInterface::addState(const std::string& state) {
    EventsComponentSystem::Instance()->addState(*this->tientity, state);
}


void TIEntityInterface::removeState(const std::string& state) {
    EventsComponentSystem::Instance()->removeState(*this->tientity, state);
}


EventState* TIEntityInterface::getState(const std::string& state) {
    EventState* eventState = EventsComponentSystem::Instance()->getState(*this->tientity, state);
    if (eventState == nullptr) {
        LogManager::Instance()->error("TIEntity " + this->tientity->getName() + " " + std::to_string(this->tientity->getId()) + " does not have event state " + state + ".");
    }
    return eventState;
}


void TIEntityInterface::setCache(sol::table& cache) {
    CacheComponentSystem::Instance()->updateCache(*this->tientity, cache);
}


sol::table& TIEntityInterface::getCache() {
    return CacheComponentSystem::Instance()->getCache(*this->tientity);
}


void TIEntityInterface::setBehaviorById(GlobalId functionId) {
    BehaviorComponentSystem::Instance()->setBehavior(*this->tientity, functionId);
}


void TIEntityInterface::setBehaviorByName(const std::string& name) {
    BehaviorComponentSystem::Instance()->setBehavior(*this->tientity, name);
}
