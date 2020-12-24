#include "managers/ScriptManager.h"

#include <string>
#include <vector>

#include <sol/sol.hpp>
#define SOL_ALL_SAFETIES_ON 1

#include "interfaces/TIEngineInterface.h"
#include "interfaces/TIEntityInterface.h"
#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"
#include "managers/HashManager.h"
#include "managers/LogManager.h"
#include "managers/WindowManager.h"
#include "managers/WorldManager.h"
#include "objects/factories/TIEntityFactory.h"
#include "utils/StringHelpers.h"

using namespace TIE;

bool ScriptManager::initialize() {

	this->luaState.open_libraries(
		sol::lib::base, 
		sol::lib::math,
		sol::lib::os,
        sol::lib::package,
		sol::lib::table
	);

    TIEngineInterface::registerUserType(this->luaState);
    TIEntityInterface::registerUserType(this->luaState);

	const std::string& startUpScript = ConfigManager::Instance()->getStartUpScript();
	if (!startUpScript.empty()) {
		this->setScriptWorkingDirectory(String::getDirectoryFromPath(startUpScript));
		this->loadScript(startUpScript);
	}

	return true;
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


template <>
void ScriptManager::runFunction<void>(const GlobalId functionId, TIEntity& tientity) {
	TIEntityInterface tientityInterface(tientity);
    TIEngineInterface engineInterface = TIEngineInterface();
	this->functions.at(functionId)(std::tuple<TIEntityInterface, TIEngineInterface>(tientityInterface, engineInterface));
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


TIEntityFactory& ScriptManager::loadTIEntityDefinition(const std::string& name, const sol::table& definition) {
	return this->loadTIEntityDefinition(name, definition, nullptr);
}


TIEntityFactory& ScriptManager::loadTIEntityDefinition(const std::string& name, const sol::table& definition, TIEntityFactory* parent) {

	TIEntityFactory& factory = this->getFactory(name, parent);
	factory.setName(name);
	std::vector<std::string> children;
	for (auto& possibleComponent : definition) {
		sol::optional<std::string> key = possibleComponent.first.as<sol::optional<std::string> >();
		sol::optional<sol::table> defintion = possibleComponent.second.as<sol::optional<sol::table> >();
		if (key && defintion) {
			if (factory.isValidComponentName(*key)) {
				this->readComponentValues(factory, *key, *defintion);
			} else {
				children.push_back(*key);
			}
		}
	}
	LogManager::Instance()->info("Registered TIEntity " + name + " from Lua script.");

	//Any other property is a child entity
	for (auto& child : children) {
		this->loadTIEntityDefinition(child, definition[child], &factory);
	}

	return factory;
}


TIEntityFactory& ScriptManager::getFactory(const std::string& name, TIEntityFactory* parent) {
	if (parent == nullptr) {
		return WorldManager::Instance()->registerTIEntity(name);
	} else {
		return parent->registerChild();
	}
}


// Iterate through each key of the table looking for values that can be casted to types.
// Store those types in the revelant TIEfactory map for use by any given component
// Call recursively if it finds another table
void ScriptManager::readComponentValues(TIEntityFactory& factory, const std::string& componentName, const sol::table& component) {
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
				factory.functionValues.insert({key, functionId });
				this->functions.insert({ functionId, value.as<sol::function>() });
			} else if (value.is<sol::table>()) {
				this->readComponentValues(factory, key, value);
			} else {
				LogManager::Instance()->error("Error casting value from script: " + key + ".");
			}
		}
	}
}

