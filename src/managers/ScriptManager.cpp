#include "managers/ScriptManager.h"

#include <string>
#include <vector>

#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"
#include "managers/LogManager.h"
#include "managers/WorldManager.h"
#include "managers/WindowManager.h"
#include "objects/factories/TIEntityFactory.h"
#include "utils/StringHelpers.h"

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
		for (auto& s = parts.begin(); s != parts.end() - 1; s++) {
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

        std::vector<std::string> tientities = Lua::getTableKeys(this->luaState, "tientities");
        if (!tientities.empty()) {
            this->loadTIEntities(tientities);
        }

		LuaRef gridTable = getGlobal(this->luaState, "world");
		TIEntity* parent = nullptr;
        if (gridTable.isTable()) {
            this->loadWorld(gridTable);
        }
    }
}


void ScriptManager::loadAssets(const luabridge::LuaRef& settingsTable, const std::string& scriptsPath) {

	LuaRef texturesTable = settingsTable["textures"];
	std::vector<std::string> texturePaths;
	if (texturesTable.isTable()) {
		texturePaths = Lua::getVector(texturesTable, texturePaths);
		for (auto& path : texturePaths) {
			AssetsManager::Instance()->loadTexturesFromPath(scriptsPath + "/" + path);
		}
	}

	LuaRef fontsTable = settingsTable["fonts"];
	std::vector<std::string> fontsPath;
	if (fontsTable.isTable()) {
		fontsPath = Lua::getVector(fontsTable, fontsPath);
		for (auto& path : fontsPath) {
			AssetsManager::Instance()->loadFontsFromPath(scriptsPath + "/" + path);
		}
	}

	LuaRef audioTable = settingsTable["audio"];
	std::vector<std::string> audioPaths;
	if (audioTable.isTable()) {
		audioPaths = Lua::getVector(audioTable, audioPaths);
		for (auto& path : audioPaths) {
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


void ScriptManager::loadWorld(const luabridge::LuaRef& worldTable) {
	TIEntityFactory factory = TIEntityFactory();
	std::vector<std::string> components = Lua::getTableKeys(this->luaState, "world");
	for (auto& component : components) {
		if (factory.isValidComponentName(component)) {
			LuaRef table = worldTable[component];
			if (table.isTable()) {
				this->readComponentValues(factory, component, table, "world." + component);
			}
		}
	}

	TIEntity& tientity = factory.build();
	WorldManager::Instance()->setLevelEntity(tientity);
	LogManager::Instance()->info("Configured world from Lua script.");

	LuaRef table = worldTable["spawns"];
	if (table.isTable()) {
		for (luabridge::Iterator iterator(table); !iterator.isNil(); ++iterator) {
			if (iterator.value().isString()) {
				WorldManager::Instance()->spawnTIEntity(iterator.value().cast<std::string>());
			}
		}
	}

}


void ScriptManager::loadTIEntities(const std::vector<std::string>& tientities) {
	LuaRef tientitiesTable = getGlobal(this->luaState, "tientities");
	for (auto& tientity : tientities) {
		ScriptManager::loadTIEntity("tientities." + tientity, tientitiesTable[tientity], nullptr);
	}
}


void ScriptManager::loadTIEntity(const std::string& tientityKey, const LuaRef& tientityTable, TIEntityFactory* parent) {

    std::vector<std::string> parts;
    String::split(tientityKey, '.', parts);
	std::string name = parts.back();
	TIEntityFactory& factory = this->getFactory(name, parent);
	std::vector<std::string> components = Lua::getTableKeys(this->luaState, tientityKey);
	std::vector<std::string> children;
	for (auto& component : components) {
		if (factory.isValidComponentName(component)) {
			LuaRef table = tientityTable[component];
			if (table.isTable()) {
				this->readComponentValues(factory, component, table, tientityKey + "." + component);
			}
		} else {
			children.push_back(component);
		}
	}

	LogManager::Instance()->info("Registered entity " + name + " from Lua script.");

	//Any other property is a child entity
	for (auto& child : children) {
		this->loadTIEntity(tientityKey + "." + child, tientityTable[child], &factory);
	}
}


TIEntityFactory& ScriptManager::getFactory(const std::string& name, TIEntityFactory* parent) {
	if (parent == nullptr) {
		return WorldManager::Instance()->registerTIEntity(name);
	} else {
		return parent->registerChild();
	}

}


void ScriptManager::readComponentValues(TIEntityFactory& factory, const std::string& component, const LuaRef& table, const std::string& globalKey) {
	std::vector<std::string> keys = Lua::getTableKeys(this->luaState, globalKey);
	for (auto& key : keys) {
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

