#include "interfaces/TIEntityInterface.h"

#include "sol/sol.hpp"

#include "componentsystems/BehaviorComponentSystem.h"
#include "componentsystems/CacheComponentSystem.h"
#include "componentsystems/EventsComponentSystem.h"
#include "componentsystems/MovesComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/SpriteComponentSystem.h"
#include "interfaces/Vector2Interface.h"
#include "managers/LogManager.h"
#include "managers/SceneManager.h"
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

    //Management
    interfaceUserType["getId"] = &TIEntityInterface::getId;
    interfaceUserType["getName"] = &TIEntityInterface::getName;
    interfaceUserType["getParent"] = &TIEntityInterface::getParent;
    interfaceUserType["getChildren"] = &TIEntityInterface::getChildren;
    interfaceUserType["spawn"] = &TIEntityInterface::spawn;
    interfaceUserType["despawn"] = &TIEntityInterface::despawn;

    //Property
    interfaceUserType["setProperty"] = &TIEntityInterface::setProperty;
    interfaceUserType["getProperty"] = &TIEntityInterface::getProperty;

    //Sprite
    interfaceUserType["setDrawn"] = &TIEntityInterface::setDrawn;
    interfaceUserType["isDrawn"] = &TIEntityInterface::isDrawn;

    //Position
	interfaceUserType["getPosition"] = &TIEntityInterface::getPosition;
	interfaceUserType["setPosition"] = &TIEntityInterface::setPosition;

    //Movement
	interfaceUserType["setDestination"] = &TIEntityInterface::setDestination;
    interfaceUserType["setDestinationByDistance"] = &TIEntityInterface::setDestinationByDistance;
	interfaceUserType["atDestination"] = &TIEntityInterface::atDestination;
    interfaceUserType["moveRight"] = &TIEntityInterface::moveRight;
    interfaceUserType["moveLeft"] = &TIEntityInterface::moveLeft;
    interfaceUserType["moveUp"] = &TIEntityInterface::moveUp;
    interfaceUserType["moveDown"] = &TIEntityInterface::moveDown;
    
    //Event
    interfaceUserType["addState"] = &TIEntityInterface::addState;
    interfaceUserType["removeState"] = &TIEntityInterface::removeState;
    interfaceUserType["getState"] = &TIEntityInterface::getState;
    
    //Cache
    interfaceUserType["setCache"] = &TIEntityInterface::setCache;
    interfaceUserType["getCache"] = &TIEntityInterface::getCache;

    //Behavior
    interfaceUserType["setBehaviorById"] = &TIEntityInterface::setBehaviorById;
    interfaceUserType["setBehaviorByName"] = &TIEntityInterface::setBehaviorByName;
}


GlobalId TIEntityInterface::getId() {
    return this->tientity->getId();
}


std::string TIEntityInterface::getName() {
    return this->tientity->getName();
}


sol::table& TIEntityInterface::getChildren() {
    this->children = ScriptManager::Instance()->getNewTable();
    for (auto& child : this->tientity->getChildren()) {
        this->children.add<TIEntityInterface>(TIEntityInterface(*child));
    }
    return children;
}


TIEntityInterface TIEntityInterface::getParent() {
    return TIEntityInterface(this->tientity->getParent());
}


TIEntityInterface TIEntityInterface::spawn(const sol::table& definition) {
    TIEntityFactory factory = TIEntityFactory(definition);
    factory.setParent(this->tientity);
    return TIEntityInterface(factory.build());
}


void TIEntityInterface::despawn() {
    this->tientity->setRemove(true);
}


void TIEntityInterface::setProperty(const std::string& key, const sol::object& value) {
    const std::string componentSystemName = ComponentSystems::getComponentNameFromKey(key);
    ComponentSystem* componentSystem = SceneManager::Instance()->getComponentSystemByComponentName(componentSystemName);
    if (componentSystem != nullptr) {
        if (value.is<float>()) {
            componentSystem->setComponentProperty(key, ScriptManager::Instance()->getValueFromObject<float>(value), *this->tientity);
        } else if (value.is<bool>()) {
            componentSystem->setComponentProperty(key, ScriptManager::Instance()->getValueFromObject<bool>(value), *this->tientity);
        } else if (value.is<std::string>()) {
            componentSystem->setComponentProperty(key, ScriptManager::Instance()->getValueFromObject<std::string>(value), *this->tientity);
        }
    }
}


std::string TIEntityInterface::getProperty(const std::string& key) {
    const std::string componentSystemName = ComponentSystems::getComponentNameFromKey(key);
    ComponentSystem* componentSystem = SceneManager::Instance()->getComponentSystemByComponentName(componentSystemName);
    if (componentSystem != nullptr) {
        return componentSystem->getComponentProperty(key, *this->tientity);
    }
    return "";
}


void TIEntityInterface::setDrawn(bool drawn) {
    ComponentSystems::setDrawn(*this->tientity, drawn);
}


bool TIEntityInterface::isDrawn() {
    return ComponentSystems::isDrawn(*this->tientity);
}


Vector2fInterface TIEntityInterface::getPosition() {
    sf::Vector2f worldPosition = PositionComponentSystem::Instance()->getWorldPosition(*this->tientity);
    return Vector2fInterface(worldPosition.x, worldPosition.y);
}


void TIEntityInterface::setPosition(const float x, const float y) {
    PositionComponentSystem::Instance()->setPosition(*this->tientity, x, y);
}


void TIEntityInterface::setDestination(const float x, const float y) {
    MovesComponentSystem::Instance()->setTargetPosition(*this->tientity, sf::Vector2f(x, y));
}


void TIEntityInterface::setDestinationByDistance(const float distance) {
    MovesComponentSystem::Instance()->setTargetPosition(*this->tientity, distance);
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
