#include "interfaces/TIEntityInterface.h"

#include "sol/sol.hpp"

#include <string>
#include <vector>

#include "componentsystems/CacheComponentSystem.h"
#include "componentsystems/MessagesComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "interfaces/MessageInterface.h"
#include "managers/ComponentSystemsManager.h"
#include "managers/ScriptManager.h"
#include "objects/GlobalId.h"
#include "objects/builders/UIElementFactoryBuilder.h"
#include "objects/factories/physics/TraceFactory.h"
#include "objects/factories/physics/CollisionBoxFactory.h"
#include "objects/factories/ui/UIElementFactory.h"
#include "managers/ScriptManager.h"
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

    //Common Child TIEntities
    interfaceUserType["addTrace"] = &TIEntityInterface::addTrace;
    interfaceUserType["addCollisionBox"] = &TIEntityInterface::addCollisionBox;
	interfaceUserType["addUIElement"] = &TIEntityInterface::addUIElement;

    //Property
    interfaceUserType["setProperty"] = &TIEntityInterface::setProperty;
    interfaceUserType["getProperty"] = &TIEntityInterface::getProperty;

    //Sprite
    interfaceUserType["setDrawn"] = &TIEntityInterface::setDrawn;
    interfaceUserType["isDrawn"] = &TIEntityInterface::isDrawn;

    //Cache
    interfaceUserType["setCache"] = &TIEntityInterface::setCache;
    interfaceUserType["getCache"] = &TIEntityInterface::getCache;
    interfaceUserType["setCacheValue"] = &TIEntityInterface::setCacheValue;
    interfaceUserType["getCacheValue"] = &TIEntityInterface::getCacheValue;
    interfaceUserType["getCacheValueOr"] = &TIEntityInterface::getCacheValueOr;

    //Search
    interfaceUserType["findTIEntitiesWithinRange"] = &TIEntityInterface::findTIEntitiesWithinRange;

    //Messages
    interfaceUserType["sendMessage"] = &TIEntityInterface::sendMessage;
}


GlobalId TIEntityInterface::getId() {
    return this->tientity->getId();
}


std::string TIEntityInterface::getName() {
    return this->tientity->getName();
}

void TIEntityInterface::setName(const std::string& name) {
    this->tientity->setName(name);
}


sol::table& TIEntityInterface::getChildren() {
    this->children = ScriptManager::Instance()->getNewTable();
    for (auto& child : this->tientity->getChildren()) {
        this->children.add<TIEntityInterface>(TIEntityInterface(*child));
    }
    return children;
}


sol::object TIEntityInterface::getChild(const std::string& name) {
    for (auto& child : this->tientity->getChildren()) {
        if (child->getName() == name) {
            return ScriptManager::Instance()->getObjectFromValue(TIEntityInterface(*child));
        }
    }
    return nullptr;
}


sol::object TIEntityInterface::getParent() {
    return ScriptManager::Instance()->getObjectFromValue(TIEntityInterface(this->tientity->getParent()));
}


sol::object TIEntityInterface::spawn(const sol::table& definition) {
    TIEntityFactory factory = TIEntityFactory(definition);
    factory.setParent(this->tientity);
    return ScriptManager::Instance()->getObjectFromValue(TIEntityInterface(factory.build()));
}


void TIEntityInterface::despawn() {
    this->tientity->setRemove(true);
}


void TIEntityInterface::setProperty(const std::string& key, const sol::object& value) {
    ComponentSystem* componentSystem = ComponentSystemsManager::Instance()->getComponentSystemForKey(key);
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
        } else if (value.is<std::vector<sf::Vector2f>>()) {
            componentSystem->setComponentProperty(key, ScriptManager::Instance()->getValueFromObject<std::vector<sf::Vector2f>>(value), *this->tientity);
        }
    }
}


sol::object TIEntityInterface::getProperty(const std::string& key) {
    ComponentSystem* componentSystem = ComponentSystemsManager::Instance()->getComponentSystemForKey(key);
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


void TIEntityInterface::setCache(sol::table& cache) {
    CacheComponentSystem::Instance()->updateCache(*this->tientity, cache);
}


sol::table& TIEntityInterface::getCache() {
    return CacheComponentSystem::Instance()->getCache(*this->tientity);
}


void TIEntityInterface::setCacheValue(const std::string& key, const sol::object& value) {
    CacheComponentSystem::Instance()->setCacheValue(*this->tientity, key, value);
}


sol::object TIEntityInterface::getCacheValue(const std::string& key) {
    return CacheComponentSystem::Instance()->getCacheValue(*this->tientity, key);
}


sol::object TIEntityInterface::getCacheValueOr(const std::string& key, const sol::object& value) {
    return CacheComponentSystem::Instance()->getCacheValueOr(*this->tientity, key, value);
}


sol::table& TIEntityInterface::findTIEntitiesWithinRange(const float range, TIEntityInterface& searchRoot) {
    this->tientitiesWithinRange = ScriptManager::Instance()->getNewTable();
    
    for (auto& tientity : PositionComponentSystem::findTIEntitiesWithinRange(*this->tientity, range, *searchRoot.tientity)) {
       this->tientitiesWithinRange.add<TIEntityInterface>(TIEntityInterface(*tientity));
    }

    return this->tientitiesWithinRange;
}


void TIEntityInterface::sendMessage(const GlobalId subscription, sol::object receivers, sol::object payload) {
    if (receivers.is<GlobalId>()) {
        MessagesComponentSystem::Instance()->sendMessage(Message(subscription, this->tientity->getId(), receivers.as<GlobalId>(), payload));
    } else if (receivers.is<sol::table>()) {
        for (auto& pair : receivers.as<sol::table>()) {
            const sol::object& reciever = pair.second;
            if (reciever.is<GlobalId>()) {
                MessagesComponentSystem::Instance()->sendMessage(Message(subscription, this->tientity->getId(), reciever.as<GlobalId>(), payload));
            }
        }
    }
}


void TIEntityInterface::addTrace(const float magnitude, const float direction) {
    TraceFactory(this->tientity).setMagnitude(magnitude).setDirection(direction).build();
}


void TIEntityInterface::addCollisionBox(const float x, const float y, const float width, const float height) {
    CollisionBoxFactory(this->tientity).setRect(x, y, width, height).build();
}


sol::object TIEntityInterface::addUIElement(const sol::table& definition) {
    return ScriptManager::Instance()->getObjectFromValue(TIEntityInterface(UIElementFactoryBuilder::make_factory(definition, this->tientity)->build()));
}
