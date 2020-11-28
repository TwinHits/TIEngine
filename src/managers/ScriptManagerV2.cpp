#include "managers/ScriptManagerV2.h"

#include <string>
#include <vector>

#include <sol/sol.hpp>

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
}
