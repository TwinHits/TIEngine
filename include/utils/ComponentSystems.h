#ifndef COMPONENTSYSTEMS_UTILS_H
#define COMPONENTSYSTEMS_UTILS_H

#include <string>

#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/ScriptManager.h"
#include "utils/types/ComponentSystemsTypes.h"

namespace TIE {
    namespace ComponentSystems {

        template <typename T>
        T getFactoryValue(const TIEntityFactory& factory, const std::string& key, T defaultReturn, TIEntity& tientity) {
            return defaultReturn;
        }

        template <>
        bool getFactoryValue<bool>(const TIEntityFactory&, const std::string&, bool, TIEntity&);

        template <>
        float getFactoryValue<float>(const TIEntityFactory&, const std::string&, float, TIEntity&);

        template<>
        std::string getFactoryValue<std::string>(const TIEntityFactory&, const std::string&, std::string, TIEntity&);

        std::string getComponentNameFromKey(const std::string&);
        ComponentSystemPropertiesMap& insertComponentPropertyIntoMap(const std::string&, ComponentSystemPropertiesMap&);
        ComponentSystemPropertiesMap& insertComponentPropertyIntoMap(const std::string&, const std::string&, ComponentSystemPropertiesMap&);

        void setDrawn(TIEntity&, bool);
        bool isDrawn(TIEntity&);
        const sf::FloatRect getGlobalBounds(TIEntity&);
        const sf::FloatRect getLocalBounds(TIEntity&);

    }
}

#endif