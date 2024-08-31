#include "managers/ScriptManager.h"

#include <string>

#include <sol/sol.hpp>
#define SOL_ALL_SAFETIES_ON 1

#include "componentsystems/CacheComponentSystem.h"
#include "interfaces/MessageInterface.h"
#include "interfaces/TIEngineInterface.h"
#include "interfaces/TIEntityInterface.h"
#include "interfaces/Vector2Interface.h"
#include "interfaces/ai/FiniteStateMachineInterface.h"
#include "managers/ConfigManager.h"
#include "managers/HashManager.h"
#include "managers/LogManager.h"
#include "managers/TimeManager.h"
#include "managers/ComponentSystemsManager.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "objects/factories/ai/FiniteStateMachineFactory.h"
#include "utils/StringHelpers.h"

using namespace TIE;

void ScriptManager::initialize() {

	this->profilerClock = &TimeManager::Instance()->addClock();

	this->luaState.open_libraries(
		sol::lib::base, 
		sol::lib::math,
		sol::lib::os,
        sol::lib::package,
		sol::lib::string,
		sol::lib::table
	);

	//Register user types with lua state
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

const GlobalId ScriptManager::registerFunction(const sol::function& function) {
    const GlobalId functionId = HashManager::Instance()->getNewGlobalId();
    this->functions.insert({ functionId, function });
	if (ConfigManager::Instance()->isLuaProfilerEnabled()) {
        // const std::string functionName = this->getFunctionName(function);
        // this->functionNames.insert({ functionId, functionName });
	}
	return functionId;
}


std::string ScriptManager::getFunctionName(sol::protected_function func) {
	// Push the function onto the stack
	lua_State* L = func.lua_state();
	func.push();

	// Use Lua's debug library to get function info
	lua_Debug ar;
	lua_getinfo(L, ">n", &ar);
	const char* func_name = lua_tostring(L, -1);
	lua_pop(L, 1); // Pop the name off the stack

	if (func_name) {
		return func_name;
	} else {
		return "unknown";
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


void ScriptManager::startProfiler(const GlobalId functionId) {
	if (ConfigManager::Instance()->isLuaProfilerEnabled()) {
		if (this->functionMetrics.count(functionId)) {
			this->functionMetrics[functionId];
		}
		profilerClock->restart();
	}
}


void ScriptManager::stopProfiler(const GlobalId functionId) {
	if (ConfigManager::Instance()->isLuaProfilerEnabled()) {
		const int elapsedTime = profilerClock->getElapsedTime().asMicroseconds();
		std::pair<long, int>& metrics = this->functionMetrics[functionId];
		// average runtime * times run + new runtime / times run plus one
		metrics.second = (metrics.second * metrics.first + elapsedTime) / ++metrics.first;
	}
}

