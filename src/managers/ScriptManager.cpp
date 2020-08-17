#include "managers/ScriptManager.h"

#include <string>
#include <vector>

#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"
#include "managers/LogManager.h"
#include "managers/WindowManager.h"
#include "objects/factories/TIEntityFactory.h"
#include "utilities/StringHelpers.h"

using namespace luabridge;
using namespace TIE;

bool ScriptManager::initialize() {
    this->luaState = luaL_newstate();
    luaL_openlibs(this->luaState);
    Lua::loadGetKeysFunction(this->luaState);

	const std::string& startUpScript = ConfigManager::Instance()->getStartUpScript();
	if (!startUpScript.empty()) {
		this->loadScript(startUpScript);
	}

	return true;
}


void ScriptManager::loadScript(const std::string& scriptPath) {
    if (Lua::loadScript(this->luaState, scriptPath)) {

		std::vector<std::string> parts;
		String::split(scriptPath, '/', parts);
		std::string scriptDirectory;
		for (auto s = parts.begin(); s != parts.end() - 1; s++) {
			scriptDirectory += *s + "/";
		}

		LuaRef windowTable = getGlobal(this->luaState, "window");
        if (windowTable.isTable()) {
            this->loadWindowProperties(windowTable);
        }

		LuaRef assetsTable = getGlobal(this->luaState, "assets");
        if (assetsTable.isTable()) {
            this->loadAssets(assetsTable, scriptDirectory);
        }

		LuaRef gridTable = getGlobal(this->luaState, "grid");
		TIEntity* parent = nullptr;
        if (gridTable.isTable()) {
            parent = this->loadGrid(gridTable);
        }

        std::vector<std::string> tientities = Lua::getTableKeys(this->luaState, "tientities");
        if (!tientities.empty()) {
            this->loadTIEntities(tientities, parent);
        }
    }
}


void ScriptManager::loadAssets(const luabridge::LuaRef& settingsTable, const std::string& scriptsPath) {

	LuaRef texturesTable = settingsTable["textures"];
	std::vector<std::string> texturePaths;
	if (texturesTable.isTable()) {
		texturePaths = Lua::getVector(texturesTable, texturePaths);
		for (auto path : texturePaths) {
			AssetsManager::Instance()->loadTexturesFromPath(scriptsPath + "/" + path);
		}
	}

	LuaRef fontsTable = settingsTable["fonts"];
	std::vector<std::string> fontsPath;
	if (fontsTable.isTable()) {
		fontsPath = Lua::getVector(fontsTable, fontsPath);
		for (auto path : fontsPath) {
			AssetsManager::Instance()->loadFontsFromPath(scriptsPath + "/" + path);
		}
	}

	LuaRef audioTable = settingsTable["audio"];
	std::vector<std::string> audioPaths;
	if (audioTable.isTable()) {
		audioPaths = Lua::getVector(audioTable, audioPaths);
		for (auto path : audioPaths) {
			AssetsManager::Instance()->loadAudioFromPath(scriptsPath + "/" + path);
		}
	}
}


void ScriptManager::loadWindowProperties(const LuaRef& windowTable) {
	LuaRef title = windowTable["title"];
	if (title.isString()) {
		WindowManager::Instance()->setTitle(title.cast<std::string>());
	} 

	LuaRef width = windowTable["width"];
	LuaRef height = windowTable["height"];
	if (width.isNumber() && height.isNumber()) {
		WindowManager::Instance()->updateWindowSize(width.cast<int>(), height.cast<int>());
	} else if (!width.isNil() || !height.isNil()) {
		std::string widthMsg = width.isNil() ? "" : std::to_string(width.cast<int>());
		std::string heightMsg = height.isNil() ? "" : std::to_string(height.cast<int>());
		LogManager::Instance()->error("Script is missing some windows size property: width: " + widthMsg + ", height: " + heightMsg);
	}
}


TIEntity* ScriptManager::loadGrid(const luabridge::LuaRef& gridTable) {
	TIEntityFactory factory = TIEntityFactory();
	std::vector<std::string> components = Lua::getTableKeys(this->luaState, "grid");
	for (auto component : components) {
		if (factory.isValidComponentName(component)) {
			LuaRef table = gridTable[component];
			if (table.isTable()) {
				this->readComponentValues(factory, component, table, "grid." + component);
			}
		}
	}
	TIEntity& tientity = factory.build();
	LogManager::Instance()->info("Configured grid from Lua script.");
	return &tientity;
}


void ScriptManager::loadTIEntities(const std::vector<std::string>& tientities, TIEntity* parent) {
	LuaRef tientitiesTable = getGlobal(this->luaState, "tientities");
	for (auto tientity : tientities) {
		ScriptManager::loadTIEntity("tientities." + tientity, tientitiesTable[tientity], parent);
	}
}


void ScriptManager::loadTIEntity(const std::string& tientityKey, const LuaRef& tientityTable, TIEntity* parent) {
	TIEntityFactory factory = TIEntityFactory();
	factory.setName(tientityKey).setParent(parent);
	std::vector<std::string> components = Lua::getTableKeys(this->luaState, tientityKey);
	std::vector<std::string> children;
	for (auto component : components) {
		if (factory.isValidComponentName(component)) {
			LuaRef table = tientityTable[component];
			if (table.isTable()) {
				this->readComponentValues(factory, component, table, tientityKey + "." + component);
			}
		} else {
			children.push_back(component);
		}
	}

	TIEntity& tientity = factory.build();
	LogManager::Instance()->info("Built entity " + tientityKey + " from Lua script.");

	//Any other property is a child entity
	for (auto& child : children) {
		this->loadTIEntity(tientityKey + "." + child, tientityTable[child], &tientity);
	}
}


void ScriptManager::readComponentValues(TIEntityFactory& factory, const std::string& component, const LuaRef& table, const std::string& globalKey) {
	std::vector<std::string> keys = Lua::getTableKeys(this->luaState, globalKey);
	for (auto key : keys) {
		LuaRef value = table[key];
		if (!value.isNil()) {
			if (value.isBool()) {
				factory.boolValues.insert({ component + "." + key, value.cast<bool>() });
			} else if (value.isNumber()) {
				factory.floatValues.insert({ component + "." + key, value.cast<float>() });
			} else if (value.isString()) {
				factory.stringValues.insert({ component + "." + key, value.cast<std::string>() });
			} else if (value.isTable()) {
				this->readComponentValues(factory, component + "." + key, value, globalKey + "." + key);
			} else {
				LogManager::Instance()->error("Error casting value from script: " + key + ".");
			}
		}
	}
}

