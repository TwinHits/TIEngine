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

void TIE::ScriptManager::runFunction(const std::string& functionKey, TIEntity& tientity) {
	if (this->functions.count(functionKey)) {
		//TIEntityInterface interface(tientity);
		//this->functions.at(functionKey)(interface);
	} else {
		LogManager::Instance()->warn("Registered function " + functionKey + " does not exist.");
	}
}
