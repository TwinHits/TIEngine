#include "managers/ScriptManager.h"

#include <string>
#include <vector>

#include <sol/sol.hpp>
#define SOL_ALL_SAFETIES_ON 1

#include "componentsystems/CacheComponentSystem.h"
#include "interfaces/EventStateInterface.h"
#include "interfaces/MessageInterface.h"
#include "interfaces/TIEngineInterface.h"
#include "interfaces/TIEntityInterface.h"
#include "interfaces/Vector2Interface.h"
#include "interfaces/ai/FiniteStateMachineInterface.h"
#include "managers/ConfigManager.h"
#include "managers/HashManager.h"
#include "managers/LogManager.h"
#include "managers/ComponentSystemsManager.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "objects/factories/ai/FiniteStateMachineFactory.h"
#include "utils/StringHelpers.h"

using namespace TIE;

void ScriptManager::initialize() {

	this->luaState.open_libraries(
		sol::lib::base, 
		sol::lib::math,
		sol::lib::os,
        sol::lib::package,
		sol::lib::string,
		sol::lib::table
	);

	//Register user types with lua state
    EventStateInterface::registerUserType(this->luaState);
    FiniteStateMachineInterface::registerUserType(this->luaState);
	MessageInterface::registerUserType(this->luaState);
    TIEngineInterface::registerUserType(this->luaState);
    TIEntityInterface::registerUserType(this->luaState);
	Vector2Interface::registerUserType(this->luaState);

  	const std::string& startUpScript = ConfigManager::Instance()->getStartUpScript();
	if (!startUpScript.empty()) {
		this->setScriptWorkingDirectory(String::getDirectoryFromPath(startUpScript));
		this->loadScript(startUpScript);
	}
}


void ScriptManager::loadScript(const std::string& scriptPath) {

    sol::load_result script = this->luaState.load_file(scriptPath);
    if (!script.valid()) {
        sol::error error = script;
        std::string errorMessage = error.what();
        LogManager::Instance()->error("Lua Script " + scriptPath + " syntax error: " + errorMessage);
    } else {
        TIEngineInterface engineInterface = TIEngineInterface();
        sol::protected_function_result result = script(engineInterface);
        if (!result.valid()) {
            sol::error error = result;
            std::string errorMessage = error.what();
            LogManager::Instance()->error("Lua Script " + scriptPath + " execution error: " + errorMessage);
        } else {
            return;
        }
    }
}


const std::string& ScriptManager::getScriptWorkingDirectory() {
    return this->scriptWorkingDirectory;
}


sol::table ScriptManager::getNewTable() {
	return sol::table(this->luaState, sol::create);
}


void ScriptManager::setScriptWorkingDirectory(const std::string& scriptWorkingDirectory) {
    this->scriptWorkingDirectory = scriptWorkingDirectory;
}


TIEntityFactory& ScriptManager::loadTIEntityDefinition(TIEntityFactory& factory, const sol::table& definition) {

	std::vector<std::string> children;
	for (auto& possibleComponent : definition) {
		sol::optional<std::string> key = possibleComponent.first.as<sol::optional<std::string> >();
		sol::optional<sol::table> definition = possibleComponent.second.as<sol::optional<sol::table> >();
		if (key && definition) {
			if (this->isValidDefinitionFieldName(*key)) {
				factory.addComponentSystemByComponentName(*key);
				this->readComponentValues(factory, *key, *definition);
			} else {
				children.push_back(*key);
			}
		}
	}

	//Any other property is a child entity
	for (auto& child : children) {
		this->loadTIEntityDefinition(factory.addChild(), definition[child]);
	}

	return factory;
}


// Iterate through each key of the table looking for values that can be casted to types.
// Store those types in the revelant TIEfactory map for use by any given component
// Call recursively if it finds another table
void ScriptManager::readComponentValues(TIEntityFactory& factory, const std::string& componentName, const sol::table& component) {
	if (componentName == CacheComponentSystem::CACHE) {
		factory.tableValues.insert({ componentName, component });
	} else {
		for (auto& pair : component) {
			const std::string& key = componentName + "." + pair.first.as<std::string>();
			const sol::object& value = pair.second;
			if (value.valid()) {
				if (value.is<bool>()) {
					factory.boolValues.insert({ key, value.as<bool>() });
				} else if (value.is<float>()) {
					factory.floatValues.insert({ key, value.as<float>() });
				} else if (value.is<std::string>()) {
					factory.stringValues.insert({ key, value.as<std::string>() });
				} else if (value.is<sol::function>()) {
					GlobalId functionId = HashManager::Instance()->getNewGlobalId();
					factory.functionValues.insert({ key, functionId });
					this->functions.insert({ functionId, value.as<sol::function>() });
				} else if (value.is<sol::table>()) {
					this->readComponentValues(factory, key, value);
				} else {
					LogManager::Instance()->error("Error casting value from script: " + key + ".");
				}
			}
		}
	}
}


bool ScriptManager::isValidDefinitionFieldName(const std::string& field) {
	return ComponentSystemsManager::Instance()->isValidComponentName(field) || field == "tientity";
 }


std::string ScriptManager::getStringFromObject(const sol::object& object) {
	if (object.is<std::string>()) {
		return object.as<std::string>();
	} else if (object.is<bool>()) {
		return std::to_string(object.as<bool>());
	} else if (object.is<float>()) {
		return std::to_string(object.as<float>());
	} else if (object.is<sf::Vector2i>()) {
		sf::Vector2i& result = object.as<sf::Vector2i>();
		return std::to_string(result.x) + ", " + std::to_string(result.y);
	} else if (object.is<sf::Vector2f>()) {
		sf::Vector2f& result = object.as<sf::Vector2f>();
		return std::to_string(result.x) + ", " + std::to_string(result.y);
	} else {
		return "";
	}
}


FiniteStateMachineFactory& ScriptManager::loadFiniteStateMachineDefinition(FiniteStateMachineFactory& factory, const sol::table& definition) {
	for (auto& pair : definition) {
		const sol::object& key = pair.first;
		const sol::object& value = pair.second;
		if (key.valid() && value.valid() && value.is<sol::function>()) {
            GlobalId functionId = HashManager::Instance()->getNewGlobalId();
            this->functions.insert({ functionId, value.as<sol::function>() });
			if (key.is<std::string>()) {
				factory.stringToFunctionValues[key.as<std::string>()] = functionId;
			} else if (key.is<GlobalId>()) {
				factory.idToFunctionValues[key.as<GlobalId>()] = functionId;
			}
		}
	}
	return factory;
}


sol::table ScriptManager::copyTable(const sol::table& original) {
	sol::table copy = this->getNewTable();
	for (auto& pair : original) {
		sol::object key = pair.first;
		sol::object value = pair.second;
        if (value.is<sol::table>()) {
            copy[key] = this->copyTable(value);
		} else {
			copy[key] = value;
		}
	}
	return copy;
}
