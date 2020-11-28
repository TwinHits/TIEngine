#include "managers/ScriptManagerV2.h"

#include <string>
#include <vector>

#include <sol/sol.hpp>
#define SOL_ALL_SAFETIES_ON 1

#include "interfaces/TIEngineInterface.h"
#include "interfaces/TIEntityInterface.h"
#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"
#include "managers/LogManager.h"
#include "managers/WindowManager.h"
#include "managers/WorldManager.h"
#include "objects/factories/TIEntityFactory.h"
#include "utils/StringHelpers.h"

using namespace TIE;

bool ScriptManagerV2::initialize() {

	this->luaState.open_libraries(
		sol::lib::base, 
		sol::lib::math,
		sol::lib::os,
        sol::lib::package
	);

    this->registerTIEngineInterface();
    this->registerTIEntityInterface();

	const std::string& startUpScript = ConfigManager::Instance()->getStartUpScript();
	if (!startUpScript.empty()) {
		this->loadScript(startUpScript);
	}

	return true;
}


void ScriptManagerV2::loadScript(const std::string& scriptPath) {

    sol::load_result script = this->luaState.load_file(scriptPath);
    if (!script.valid()) {
        sol::error error = script;
        std::string errorMessage = error.what();
        LogManager::Instance()->error("Lua Script " + scriptPath + " syntax error: " + errorMessage);
    } else {
        TIEngineInterface engineInterface = TIEngineInterface();
        engineInterface.setScriptWorkingDirectory(String::getDirectoryFromPath(scriptPath));
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


TIEntityFactory& ScriptManagerV2::loadTIEntityDefinition(const std::string& name, const sol::table& definition) {
	return this->loadTIEntityDefinition(name, definition, nullptr);
}


TIEntityFactory& ScriptManagerV2::loadTIEntityDefinition(const std::string& name, const sol::table& definition, TIEntityFactory* parent) {

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


TIEntityFactory& ScriptManagerV2::getFactory(const std::string& name, TIEntityFactory* parent) {
	if (parent == nullptr) {
		return WorldManager::Instance()->registerTIEntity(name);
	} else {
		return parent->registerChild();
	}
}


// Iterate through each key of the table looking for values that can be casted to types.
// Store those types in the revelant TIEfactory map for use by any given component
// Call recursively if it finds another table
void ScriptManagerV2::readComponentValues(TIEntityFactory& factory, const std::string& componentName, const sol::table& component) {
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
				factory.stringValues.insert({ key, key });
				//this->functions.insert({ key, value.as<sol::function>() });
			} else if (value.is<sol::table>()) {
				this->readComponentValues(factory, key, value);
			} else {
				LogManager::Instance()->error("Error casting value from script: " + key + ".");
			}
		}
	}
}


void ScriptManagerV2::registerTIEntityInterface() {
    sol::usertype<TIEntityInterface> interfaceUserType = this->luaState.new_usertype<TIEntityInterface>("tientity");
	interfaceUserType["getPosition"] = &TIEntityInterface::getPosition;
    interfaceUserType["moveRight"] = &TIEntityInterface::moveRight;
    interfaceUserType["moveLeft"] = &TIEntityInterface::moveLeft;
    interfaceUserType["moveUp"] = &TIEntityInterface::moveUp;
    interfaceUserType["moveDown"] = &TIEntityInterface::moveDown;
    interfaceUserType["spawn"] = &TIEntityInterface::spawn;
}


void ScriptManagerV2::registerTIEngineInterface() {
	sol::usertype<TIEngineInterface> engineInterfaceUserType = this->luaState.new_usertype<TIEngineInterface>("tiengine");
    engineInterfaceUserType["isValid"] = &TIEngineInterface::isValid;
    engineInterfaceUserType["registerTexturesDirectory"] = &TIEngineInterface::registerTexturesDirectory;
    engineInterfaceUserType["registerFontDirectory"] = &TIEngineInterface::registerFontsDirectory;
    engineInterfaceUserType["registerAudioDirectory"] = &TIEngineInterface::registerAudioDirectory;
    engineInterfaceUserType["setWindowTitle"] = &TIEngineInterface::setWindowTitle;
    engineInterfaceUserType["setWindowSize"] = &TIEngineInterface::setWindowSize;
	engineInterfaceUserType["registerTIEntity"] = &TIEngineInterface::registerTIEntityDefinition;
}

