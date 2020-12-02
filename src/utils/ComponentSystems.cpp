#include "utils/ComponentSystems.h"

using namespace TIE;

template <>
bool ComponentSystems::getFactoryValue<bool>(const TIEntityFactory& factory, const std::string& key, bool defaultReturn, TIEntity& tientity) {
    if (factory.boolValues.count(key)) {
        return factory.boolValues.at(key);
    } else if (factory.functionValues.count(key)) {
        return ScriptManager::Instance()->runFunction<bool>(factory.functionValues.at(key), tientity);
    } else {
        return defaultReturn;
    }
}

template <>
float ComponentSystems::getFactoryValue<float>(const TIEntityFactory& factory, const std::string& key, float defaultReturn, TIEntity& tientity) {
    if (factory.floatValues.count(key)) {
        return factory.floatValues.at(key);
    } else if (factory.functionValues.count(key)) {
        return ScriptManager::Instance()->runFunction<float>(factory.functionValues.at(key), tientity);
    } else {
        return defaultReturn;
    }
}

template <>
std::string ComponentSystems::getFactoryValue<std::string>(const TIEntityFactory& factory, const std::string& key, std::string defaultReturn, TIEntity& tientity) {
    if (factory.stringValues.count(key)) {
        return factory.stringValues.at(key);
    } else if (factory.functionValues.count(key)) {
        return ScriptManager::Instance()->runFunction<std::string>(factory.functionValues.at(key), tientity);
    } else {
        return defaultReturn;
    }
}
