#ifndef COMPONENTSYSTEMS_UTILS_H
#define COMPONENTSYSTEMS_UTILS_H

#include <string>

#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/ScriptManager.h"

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

        void setDrawn(TIEntity&, bool);
        bool isDrawn(TIEntity&);
    }
}

#endif