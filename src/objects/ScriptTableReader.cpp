#include "objects/ScriptTableReader.h"

#include <map>
#include <string>

#include "componentsystems/CacheComponentSystem.h"
#include "managers/ComponentSystemsManager.h"
#include "managers/LogManager.h"
#include "managers/ScriptManager.h"
#include "templates/MakeUnique.h"

using namespace TIE;

ScriptTableReader::ScriptTableReader(const sol::table& table) : ScriptTableReader() {
    this->read(table);
}


ScriptTableReader::ScriptTableReader() {
}


const bool ScriptTableReader::hasKey(const std::string& key) const {
    return this->keys.count(key);
}


const ScriptTableReader& ScriptTableReader::getReader(const std::string& key) const {
    if (!this->readers.count(key)) {
        return this->getEmptyReader();
    }
    return this->readers.at(key);
}


const std::map<std::string, ScriptTableReader>& ScriptTableReader::getReaders() const {
    return this->readers;
}


const ScriptTableReader& ScriptTableReader::getEmptyReader() {
    static const ScriptTableReader emptyReader = ScriptTableReader();
    return emptyReader;
}


void ScriptTableReader::read(const sol::table& table) {
    for (auto& [tableKey, value] : table) {
        if (tableKey.is<std::string>() || tableKey.is<int>()) {
            std::string key;
            if (tableKey.is<int>()) {
                key = std::to_string(tableKey.as<int>());
            } else {
                key = tableKey.as<std::string>();
            }
            this->keys[key] = true;
            if (value.valid()) {
                if (value.is<bool>()) {
                    this->boolValues.insert({ key, value.as<bool>() });
                } else if (value.is<float>()) {
                    this->floatValues.insert({ key, value.as<float>() });
                } else if (value.is<std::string>()) {
                    this->stringValues.insert({ key, value.as<std::string>() });
                } else if (value.is<sol::function>()) {
                    this->functionValues.insert({ key, ScriptManager::Instance()->registerFunction(value.as<sol::function>()) });
                } else if (value.is<sol::table>()) {
                    this->tableValues.insert({ key, value.as<sol::table>() });
                    this->readers.insert({key, ScriptTableReader(value.as<sol::table>())});
                } else {
                    LogManager::Instance()->error("Error casting value from script: " + key + ".");
                }
            }
        }
    }
}
