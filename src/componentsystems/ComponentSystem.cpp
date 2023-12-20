#include "componentsystems/ComponentSystem.h"

#include <string>

#include "objects/tientities/TIEntity.h"
#include "utils/ComponentSystems.h"

using namespace TIE;

const std::string& ComponentSystem::getName() {
    return this->name;
}

void ComponentSystem::addPropertyToComponentPropertyMap(const std::string& property) {
	this->componentPropertyMap[property] = property;
}


void ComponentSystem::setName(const std::string& name) {
    this->name = name;
}


void ComponentSystem::setComponentProperty(const std::string& key, bool value, TIEntity& tientity) {}


void ComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity) {}


void ComponentSystem::setComponentProperty(const std::string& key, const std::string& value, TIEntity& tientity) {}


void ComponentSystem::setComponentProperty(const std::string& key, const sf::Vector2f& value, TIEntity& tientity) {}


void ComponentSystem::setComponentProperty(const std::string& key, const sf::Vector2i& value, TIEntity& tientity) {}


sol::object ComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
    return ScriptManager::Instance()->getObjectFromValue(nullptr);
}


ComponentSystems::ComponentSystemPropertiesMap& ComponentSystem::populateComponentSystemsPropertiesMap(ComponentSystems::ComponentSystemPropertiesMap& map) {
    map[this->getName()] = this->componentPropertyMap;
    return map;
}


std::string ComponentSystem::getComponentPropertiesString(TIEntity& tientity) {
    if (this->hasComponent(tientity)) {
        std::stringstream ss;
        ss << this->getName() << ":" << std::endl;
        ss << "-------" << std::endl;
        for (auto& componentPropertyPair : this->componentPropertyMap) {
            sol::object property = this->getComponentProperty(componentPropertyPair.second, tientity);
            ss << componentPropertyPair.first << ": " << ScriptManager::Instance()->getStringFromObject(property) << std::endl;
        }
        ss << std::endl;
        return ss.str();
    }
    return "";
}
