#include "interfaces/TIEntityInterface.h"

#include "sol/sol.hpp"

#include "componentsystems/CacheComponentSystem.h"
#include "componentsystems/EventsComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/SpriteComponentSystem.h"
#include "managers/SceneManager.h"
#include "objects/GlobalId.h"
#include "objects/components/structs/EventState.h"
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
    interfaceUserType["setName"] = &TIEntityInterface::setName;
    interfaceUserType["getParent"] = &TIEntityInterface::getParent;
    interfaceUserType["getChildren"] = &TIEntityInterface::getChildren;
    interfaceUserType["getChild"] = &TIEntityInterface::getChild;
    interfaceUserType["spawn"] = &TIEntityInterface::spawn;
    interfaceUserType["despawn"] = &TIEntityInterface::despawn;

    //Property
    interfaceUserType["setProperty"] = &TIEntityInterface::setProperty;
    interfaceUserType["getProperty"] = &TIEntityInterface::getProperty;

    //Sprite
    interfaceUserType["setDrawn"] = &TIEntityInterface::setDrawn;
    interfaceUserType["isDrawn"] = &TIEntityInterface::isDrawn;

    //Event
    interfaceUserType["addState"] = &TIEntityInterface::addState;
    interfaceUserType["removeState"] = &TIEntityInterface::removeState;
    interfaceUserType["getState"] = &TIEntityInterface::getState;
    
    //Cache
    interfaceUserType["setCache"] = &TIEntityInterface::setCache;
    interfaceUserType["getCache"] = &TIEntityInterface::getCache;

    //Search
    interfaceUserType["findTIEntitiesWithinRange"] = &TIEntityInterface::findTIEntitiesWithinRange;
}


GlobalId TIEntityInterface::getId() {
    return this->tientity->getId();
}


std::string TIEntityInterface::getName() {
    return this->tientity->getName();
}

void TIEntityInterface::setName(const std::string& name) {
    return this->tientity->setName(name);
}


sol::table& TIEntityInterface::getChildren() {
    this->children = ScriptManager::Instance()->getNewTable();
    for (auto& child : this->tientity->getChildren()) {
        this->children.add<TIEntityInterface>(TIEntityInterface(*child));
    }
    return children;
}


TIEntityInterface TIEntityInterface::getChild(const std::string& name) {
    for (auto& child : this->tientity->getChildren()) {
        if (child->getName() == name) {
            return TIEntityInterface(*child);
        }
    }
    return nullptr;
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
    ComponentSystem* componentSystem = SceneManager::Instance()->getComponentSystemByComponentName(ComponentSystems::getComponentNameFromKey(key));
    if (componentSystem != nullptr) {
        if (value.is<float>()) {
            componentSystem->setComponentProperty(key, ScriptManager::Instance()->getValueFromObject<float>(value), *this->tientity);
        } else if (value.is<bool>()) {
            componentSystem->setComponentProperty(key, ScriptManager::Instance()->getValueFromObject<bool>(value), *this->tientity);
        } else if (value.is<std::string>()) {
            componentSystem->setComponentProperty(key, ScriptManager::Instance()->getValueFromObject<std::string>(value), *this->tientity);
        } else if (value.is<sf::Vector2f>()) {
            componentSystem->setComponentProperty(key, ScriptManager::Instance()->getValueFromObject<sf::Vector2f>(value), *this->tientity);
        } else if (value.is<sf::Vector2i>()) {
            componentSystem->setComponentProperty(key, ScriptManager::Instance()->getValueFromObject<sf::Vector2i>(value), *this->tientity);
        }
    }
}


sol::object TIEntityInterface::getProperty(const std::string& key) {
    ComponentSystem* componentSystem = SceneManager::Instance()->getComponentSystemByComponentName(ComponentSystems::getComponentNameFromKey(key));
    if (componentSystem != nullptr) {
        return componentSystem->getComponentProperty(key, *this->tientity);
    }
    return ScriptManager::Instance()->getObjectFromValue(nullptr);
}


void TIEntityInterface::setDrawn(bool drawn) {
    ComponentSystems::setDrawn(*this->tientity, drawn);
}


bool TIEntityInterface::isDrawn() {
    return ComponentSystems::isDrawn(*this->tientity);
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

sol::table& TIEntityInterface::findTIEntitiesWithinRange(const float range, TIEntityInterface& searchRoot) {
    this->tientitiesWithinRange = ScriptManager::Instance()->getNewTable();
    
    for (auto& tientity : PositionComponentSystem::findTIEntitiesWithinRange(*this->tientity, range, *searchRoot.tientity)) {
       this->tientitiesWithinRange.add<TIEntityInterface>(TIEntityInterface(*tientity));
    }

    return this->tientitiesWithinRange;
}
