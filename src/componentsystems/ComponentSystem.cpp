#include "componentsystems/ComponentSystem.h"

#include <string>

#include "managers/ComponentSystemsManager.h"
#include "managers/ScriptManager.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

const std::string& ComponentSystem::getName() {
    return this->name;
}


void ComponentSystem::setName(const std::string& name) {
    this->name = name;
}


void ComponentSystem::setComponentProperty(const std::string& key, bool value, TIEntity& tientity) {}


void ComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity) {}


void ComponentSystem::setComponentProperty(const std::string& key, const std::string& value, TIEntity& tientity) {}


void ComponentSystem::setComponentProperty(const std::string& key, const sf::Vector2f& value, TIEntity& tientity) {}


void ComponentSystem::setComponentProperty(const std::string& key, const sf::Vector2i& value, TIEntity& tientity) {}


void ComponentSystem::setComponentProperty(const std::string& key, const std::vector<sf::Vector2f>& value, TIEntity& tientity) {}


sol::object ComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
    return ScriptManager::Instance()->getObjectFromValue(nullptr);
}


std::string ComponentSystem::getComponentPropertiesString(TIEntity& tientity) {
    if (this->hasComponent(tientity)) {
        std::stringstream ss;
        ss << this->getName() << ":" << std::endl;
        ss << "-------" << std::endl;
        for (auto& componentPropertyPair : ComponentSystemsManager::Instance()->getComponentSystemPropertyMap(this->getName())) {
            sol::object property = this->getComponentProperty(componentPropertyPair.second, tientity);
            ss << componentPropertyPair.first << ": " << ScriptManager::Instance()->getStringFromObject(property) << std::endl;
        }
        ss << "-------" << std::endl;
        ss << std::endl;
        return ss.str();
    }
    return "";
}
