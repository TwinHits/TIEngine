#include "managers/ScriptManager.h"

#include <string>
#include <vector>

#include <sol/sol.hpp>

#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"
#include "managers/LogManager.h"
#include "managers/WindowManager.h"
#include "managers/WorldManager.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntityScriptInterface.h"
#include "utils/StringHelpers.h"

using namespace TIE;

bool ScriptManager::initialize() {

	this->luaState.open_libraries(sol::lib::base);

	const std::string& startUpScript = ConfigManager::Instance()->getStartUpScript();
	if (!startUpScript.empty()) {
		this->loadScript(startUpScript);
	}

	return true;
}

void ScriptManager::loadScript(const std::string& scriptPath) {
	this->luaState.script_file(scriptPath);

    std::vector<std::string> parts;
    String::split(scriptPath, '/', parts);
    std::string scriptDirectory;
    for (auto& s = parts.begin(); s != parts.end() - 1; s++) {
        scriptDirectory += *s + "/";
    }

    sol::optional<sol::table> assetsTable = this->luaState["assets"];
    if (assetsTable && (*assetsTable).valid()) {
        this->loadAssets(*assetsTable, scriptDirectory);
    }

    sol::optional<sol::table> windowTable = this->luaState["window"];
    if (windowTable && (*windowTable).valid()) {
        this->loadWindowProperties(*windowTable);
    }


    sol::optional<sol::table> tientitiesTable = this->luaState["tientities"];
    if (tientitiesTable && (*tientitiesTable).valid()) {
        this->loadTIEntities(*tientitiesTable);
	}

    sol::optional<sol::table> worldTable = this->luaState["world"];
    if (worldTable && (*worldTable).valid()) {
        this->loadWorld(*worldTable);
    }
}

void TIE::ScriptManager::runFunction(const std::string& functionKey, TIEntity& tientity) {
	if (this->functions.count(functionKey)) {
		/*
		this->luaState.set_function("moveRight", &TIEntityScriptInterface::moveRight);
		*/

		/*
		this->luaState.new_usertype<TIEntityScriptInterface>("tientity", sol::no_constructor,
			"moveRight", &TIEntityScriptInterface::moveRight);
		*/

		//sol::usertype<TIEntityScriptInterface> interface_type = this->luaState.new_usertype<TIEntityScriptInterface>("tientity", "moveRight", &TIEntityScriptInterface::moveRight);
		sol::usertype<TIEntityScriptInterface> interface_type = this->luaState.new_usertype<TIEntityScriptInterface>("tientity");
		//interface_type["moveRight"] = &TIEntityScriptInterface::moveRight;

		TIEntityScriptInterface interface(tientity);
		this->functions.at(functionKey)(interface);
	} else {
		LogManager::Instance()->warn("Registered function " + functionKey + " does not exist.");
	}
}


void ScriptManager::loadAssets(const sol::table& settingsTable, const std::string& scriptsPath) {

	sol::optional<sol::table> texturesPaths = settingsTable["textures"];
	if (texturesPaths && (*texturesPaths).valid()) {
		for (auto& i : *texturesPaths) {
			sol::optional<std::string> path = i.second.as<sol::optional<std::string> >();
			if (path) {
				AssetsManager::Instance()->loadTexturesFromPath(scriptsPath + *path);
			}
		}
	}

	sol::optional<sol::table> fontPaths = settingsTable["fonts"];
	if (fontPaths && (*fontPaths).valid()) {
		for (auto& i : *fontPaths) {
			sol::optional<std::string> path = i.second.as<sol::optional<std::string> >();
			if (path) {
				AssetsManager::Instance()->loadFontsFromPath(scriptsPath + *path);
			}
		}
	}

	sol::optional<sol::table> audioPaths = settingsTable["audio"];
	if (audioPaths && (*audioPaths).valid()) {
		for (auto& i : *audioPaths) {
			sol::optional<std::string> path = i.second.as<sol::optional<std::string> >();
			if (path) {
				AssetsManager::Instance()->loadAudioFromPath(scriptsPath + *path);
			}
		}
	}
}


void ScriptManager::loadWindowProperties(const sol::table& windowTable) {
	sol::optional<std::string> title = windowTable["title"];
	if (title) {
		WindowManager::Instance()->setTitle(*title);
	}

	sol::optional<int> width = windowTable["width"];
	sol::optional<int> height = windowTable["height"];
	if (width && height) {
		WindowManager::Instance()->updateWindowSize(*width, *height);
	} else if (!width || !height) {
		std::string widthMsg = width ? "" : std::to_string(*width);
		std::string heightMsg = height ? "" : std::to_string(*height);
		LogManager::Instance()->error("Script is missing some windows size property: width: " + widthMsg + ", height: " + heightMsg);
	}
}


void ScriptManager::loadWorld(const sol::table& worldTable) {
	TIEntityFactory factory = TIEntityFactory();
	for (auto& component : worldTable) {
		sol::optional<std::string> componentName = component.first.as<sol::optional<std::string> >();
		if (componentName && factory.isValidComponentName(*componentName)) {
			sol::optional<sol::table> table = worldTable[*componentName];
			if (table && (*table).valid()) {
				this->readComponentValues(factory, *componentName, *table);
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


void ScriptManager::loadTIEntities(const sol::table& tientities) {
	for (auto& tientity : tientities) {
		sol::optional<std::string> name = tientity.first.as<sol::optional<std::string> >();
		sol::optional<sol::table> defintion = tientity.second.as<sol::optional<sol::table> >();
		if (name && defintion) {
			ScriptManager::loadTIEntity(*name, *defintion, nullptr);
		}
	}
}


TIEntityFactory& ScriptManager::loadTIEntity(const std::string& name, const sol::table& tientityTable, TIEntityFactory* parent) {

	TIEntityFactory& factory = this->getFactory(name, parent);
	std::vector<std::string> children;
	for (auto& possibleComponent : tientityTable) {
		sol::optional<std::string> componentName = possibleComponent.first.as<sol::optional<std::string> >();
		sol::optional<sol::table> defintion = possibleComponent.second.as<sol::optional<sol::table> >();
		if (componentName && defintion) {
			if (factory.isValidComponentName(*componentName)) {
				this->readComponentValues(factory, *componentName, *defintion);
			} else {
				children.push_back(*componentName);
			}
		}
	}

	LogManager::Instance()->info("Registered entity " + name + " from Lua script.");

	//Any other property is a child entity
	for (auto& child : children) {
		this->loadTIEntity(child, tientityTable[child], &factory);
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
				factory.stringValues.insert({ key, key });
				this->functions.insert({ key, value.as<sol::function>() });
			} else if (value.is<sol::table>()) {
				this->readComponentValues(factory, key, value);
			} else {
				LogManager::Instance()->error("Error casting value from script: " + key + ".");
			}
		}
	}
}
