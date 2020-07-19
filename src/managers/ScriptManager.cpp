#include "managers/ScriptManager.h"

#include <algorithm>
#include <string>
#include <vector>

#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"
#include "managers/LogManager.h"
#include "managers/SceneManager.h"
#include "managers/WindowManager.h"
#include "objects/factories/TIEntityFactory.h"
#include "templates/VectorHelpers.h"
#include "utilities/StringHelpers.h"

using namespace luabridge;
using namespace TIE;

bool ScriptManager::initialize() {
    this->luaState = luaL_newstate();
    luaL_openlibs(this->luaState);
    Lua::loadGetKeysFunction(this->luaState);
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

        std::vector<std::string> tientities = Lua::getTableKeys(this->luaState, "tientities");
        if (!tientities.empty()) {
            this->loadTIEntities(tientities);
        }
    }
}


void TIE::ScriptManager::loadAssets(const luabridge::LuaRef& settingsTable, const std::string& scriptsPath) {

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


void ScriptManager::loadTIEntities(const std::vector<std::string>& tientities) {
	LuaRef tientitiesTable = getGlobal(this->luaState, "tientities");
	for (auto tientity : tientities) {
		ScriptManager::loadTIEntity("tientities." + tientity, tientitiesTable[tientity], nullptr);
	}
}


void ScriptManager::loadTIEntity(const std::string& tientityKey, const LuaRef& tientityTable, TIEntity* parent) {
    TIEntityFactory tientityFactory = TIEntityFactory();
	tientityFactory.setParent(parent).setName(tientityKey);
    std::vector<std::string> children = Lua::getTableKeys(this->luaState, tientityKey);

    //Any known property name is a component of this entity
	LuaRef drawnTable = tientityTable[TIEntityFactory::DRAWN];
	if (drawnTable.isTable()) {
		Vector::remove(children, std::string(TIEntityFactory::DRAWN));

		LuaRef drawn = drawnTable[TIEntityFactory::DRAWN];
		if (drawn.isBool()) {
			tientityFactory.setDrawn(drawn.cast<bool>());
		} else if (!drawn.isNil()) {
			LogManager::Instance()->error("Error casting value from script: " + tientityKey + "." + TIEntityFactory::DRAWN);
		}

		LuaRef texture = drawnTable[TIEntityFactory::TEXTURE];
		if (texture.isString()) {
			tientityFactory.setTexture(texture.cast<std::string>());
		} else if (!texture.isNil()) {
			LogManager::Instance()->error("Error casting value from script: " + tientityKey + "." + TIEntityFactory::TEXTURE);
		}

		LuaRef text = drawnTable[TIEntityFactory::TEXT];
		if (text.isString()) {
			tientityFactory.setText(text.cast<std::string>());
		} else if (!text.isNil()) {
			LogManager::Instance()->error("Error casting value from script: " + tientityKey + "." + TIEntityFactory::TEXT);
		}
	}

	LuaRef movesTable = tientityTable[TIEntityFactory::MOVES];
	if (movesTable.isTable()) {
		Vector::remove(children, std::string(TIEntityFactory::MOVES));

		LuaRef speed = movesTable[TIEntityFactory::SPEED];
		if (speed.isNumber()) {
			tientityFactory.setSpeed(speed.cast<float>());
		} else if (!speed.isNil()) {
			LogManager::Instance()->error("Error casting value from script: " + tientityKey + "." + TIEntityFactory::SPEED);
		}

		LuaRef direction = movesTable[TIEntityFactory::DIRECTION];
		if (direction.isNumber()) {
			tientityFactory.setDirection(direction.cast<float>());
		} else if (!direction.isNil()) {
			LogManager::Instance()->error("Error casting value from script: " + tientityKey + "." + TIEntityFactory::DIRECTION);
		}
	}

	LuaRef selectableTable = tientityTable[TIEntityFactory::SELECTABLE];
	if (selectableTable.isTable()) {
		Vector::remove(children, std::string(TIEntityFactory::SELECTABLE));

		LuaRef selectable = selectableTable[TIEntityFactory::SELECTABLE];
		if (selectable.isBool()) {
			tientityFactory.setSelectable(selectable.cast<bool>());
		} else if (!selectable.isNil()) {
			LogManager::Instance()->error("Error casting value from script: " + tientityKey + "." + TIEntityFactory::SELECTABLE);
		}
	}

	LuaRef eventsTable = tientityTable[TIEntityFactory::EVENTS];
	if (eventsTable.isTable()) {
		Vector::remove(children, std::string(TIEntityFactory::EVENTS));

		LuaRef selectableEventTable = eventsTable[TIEntityFactory::SELECTED];
		selectableEventTable.length();
		if (selectableEventTable.isTable()) {
			LuaRef click = selectableEventTable[TIEntityFactory::CLICK];
			if (click.isString()) {
				tientityFactory.setClick(click.cast<std::string>());
			}
			else if (!click.isNil()) {
				LogManager::Instance()->error("Error casting value from script: " + tientityKey + "." + TIEntityFactory::EVENTS);
			}
		}
	}

    TIEntity& tientity = tientityFactory.build();
	LogManager::Instance()->info("Built entity " + tientityKey + " from Lua script.");

    //Any other property is a child entity
	for (auto& child : children) {
		this->loadTIEntity(tientityKey + "." + child, tientityTable[child], &tientity);
	}
}
