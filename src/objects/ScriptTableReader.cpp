#include "objects/ScriptTableReader.h"

#include <map>
#include <string>

#include "componentsystems/CacheComponentSystem.h"
#include "managers/ComponentSystemsManager.h"
#include "managers/LogManager.h"
#include "managers/ScriptManager.h"
#include "templates/MakeUnique.h"

using namespace TIE;

ScriptTableReader::ScriptTableReader(const sol::table& table) {
    this->read(table);
}


void ScriptTableReader::read(const sol::table& table) {
    this->read("", table);
}


const bool ScriptTableReader::hasKey(const std::string& key) {
    return this->keys.count(key);
}


void ScriptTableReader::read(const std::string & prefix, const sol::table& table) {
    for (auto& [key, value] : table) {
        if (key.is<std::string>()) {
            const std::string& prefixedKey = prefix + key.as<std::string>();
            this->keys[prefixedKey] = true;
            if (value.valid()) {
                if (value.is<bool>()) {
                    this->boolValues.insert({ prefixedKey, value.as<bool>() });
                } else if (value.is<float>()) {
                    this->floatValues.insert({ prefixedKey, value.as<float>() });
                } else if (value.is<std::string>()) {
                    this->stringValues.insert({ prefixedKey, value.as<std::string>() });
                } else if (value.is<sol::function>()) {
                    this->functionValues.insert({ prefixedKey, ScriptManager::Instance()->registerFunction(value.as<sol::function>()) });
                } else if (value.is<sol::table>()) {
                    this->tableValues.insert({ prefixedKey, value.as<sol::table>() });
                    this->read(prefixedKey + '.', value.as<sol::table>());
                } else {
                    LogManager::Instance()->error("Error casting value from script: " + prefixedKey + ".");
                }
            }
        }
    }
}
