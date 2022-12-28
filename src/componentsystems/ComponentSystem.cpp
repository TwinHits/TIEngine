#include "componentsystems/ComponentSystem.h"

#include "managers/ScriptManager.h"

using namespace TIE;

bool ComponentSystem::setComponentProperty(const std::string& key, bool value, TIEntity& tientity) {
    return false;
}


bool ComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity) {
    return false;
}


bool ComponentSystem::setComponentProperty(const std::string& key, const std::string& value, TIEntity& tientity) {
    return false;
}


bool ComponentSystem::setComponentProperty(const std::string& key, const sf::Vector2f& value, TIEntity& tientity) {
    return false;
}


bool ComponentSystem::setComponentProperty(const std::string& key, const sf::Vector2i& value, TIEntity& tientity) {
    return false;
}


ComponentSystems::ComponentSystemPropertiesMap& ComponentSystem::populateComponentSystemsPropertiesMap(ComponentSystems::ComponentSystemPropertiesMap& map) {
    map[this->getName()] = this->componentPropertyMap;
    return map;
}



std::string ComponentSystem::getComponentPropertiesString(TIEntity& tientity) {
    if (this->hasComponent(tientity)) {
        std::stringstream ss;
        ss << this->getName() << std::endl;
        for (auto& componentPropertyPair : this->componentPropertyMap) {
            sol::object property = this->getComponentProperty(componentPropertyPair.second, tientity);
            ss << componentPropertyPair.first << ": " << ScriptManager::Instance()->getStringFromObject(property) << std::endl;
        }
        ss << std::endl;
        return ss.str();
    }
    return "";
}

