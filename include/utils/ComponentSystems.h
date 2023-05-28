#ifndef COMPONENTSYSTEMS_UTILS_H
#define COMPONENTSYSTEMS_UTILS_H

#include <string>

#include "objects/ScriptTableReader.h"
#include "objects/tientities/TIEntity.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "managers/ScriptManager.h"
#include "utils/types/ComponentSystemsTypes.h"

namespace TIE {
    namespace ComponentSystems {

        std::string getComponentNameFromKey(const std::string&);
        ComponentSystemPropertiesMap& insertComponentPropertyIntoMap(const std::string&, ComponentSystemPropertiesMap&);
        ComponentSystemPropertiesMap& insertComponentPropertyIntoMap(const std::string&, const std::string&, ComponentSystemPropertiesMap&);
        ComponentSystemPropertyMap& insertComponentPropertyIntoMap(const std::string&, ComponentSystemPropertyMap&);
        ComponentSystemPropertyMap& insertComponentPropertyIntoMap(const std::string&, const std::string&, ComponentSystemPropertyMap&);

        void setDrawn(TIEntity&, bool);
        bool isDrawn(TIEntity&);
        const sf::FloatRect getGlobalBounds(TIEntity&);
        const sf::FloatRect getLocalBounds(TIEntity&);

    }
}

#endif