#include "managers/ScriptManager.h"

#include <string>
#include <vector>

#include <sol/sol.hpp>

#include "interfaces/TIEntityInterface.h"
#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"
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
		sol::lib::os
	);

	return true;
}

void ScriptManager::loadScript(const std::string& scriptPath) {

    sol::optional<sol::table> worldTable = this->luaState["world"];
    if (worldTable && (*worldTable).valid()) {
        this->loadWorld(*worldTable);
    }
}

void TIE::ScriptManager::runFunction(const std::string& functionKey, TIEntity& tientity) {
	if (this->functions.count(functionKey)) {
		//TIEntityInterface interface(tientity);
		//this->functions.at(functionKey)(interface);
	} else {
		LogManager::Instance()->warn("Registered function " + functionKey + " does not exist.");
	}
}

void ScriptManager::loadWorld(const sol::table& worldTable) {
	TIEntityFactory factory = TIEntityFactory();
	for (auto& component : worldTable) {
		sol::optional<std::string> componentName = component.first.as<sol::optional<std::string> >();
		if (componentName && factory.isValidComponentName(*componentName)) {
			sol::optional<sol::table> table = worldTable[*componentName];
			if (table && (*table).valid()) {
				//this->readComponentValues(factory, *componentName, *table);
			}
		}
	}

	TIEntity& tientity = factory.build();
	WorldManager::Instance()->setLevelEntity(tientity);
	LogManager::Instance()->info("Configured world from Lua script.");
	sol::optional<sol::table> spawns = worldTable["spawns"];
	if (spawns && (*spawns).valid()) {
		for (auto& i : *spawns) {
			sol::optional<std::string> spawn = i.second.as<sol::optional<std::string> >();
			if (spawn) {
				WorldManager::Instance()->spawnTIEntity(*spawn);
			}
		}
	}

}

