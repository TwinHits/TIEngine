#include <iostream>
#include <string>

#include "managers/ConfigManager.h"
#include "managers/LogManager.h"
#include "managers/ScriptManager.h"
#include "managers/WindowManager.h"
#include "managers/ViewManager.h"

using namespace luabridge;
using namespace TIE;

ScriptManager::ScriptManager() {
    this->luaState = luaL_newstate();
}


ScriptManager::~ScriptManager() {

}

void ScriptManager::loadScript(const std::string& scriptName) {

    const std::string& scriptsPath = ConfigManager::Instance()->getScriptsPath();
    std::string scriptFile = scriptsPath + scriptName;

    luaL_dofile(this->luaState, scriptFile.c_str());
    luaL_openlibs(this->luaState);
    lua_pcall(this->luaState, 0, 0, 0);

    LuaRef windowProperties = getGlobal(this->luaState, "window");
    this->loadWindowProperties(windowProperties);

    LuaRef tientityDefinitions = getGlobal(this->luaState, "tientities");
    this->loadTIEntityDefinitions(tientityDefinitions);
}

void ScriptManager::loadWindowProperties(LuaRef windowProperties) {
    LuaRef titleProp = windowProperties["title"];
    LuaRef widthProp = windowProperties["width"];
    LuaRef heightProp = windowProperties["height"];

    std::string title = titleProp.cast<std::string>();
    int width = widthProp.cast<int>();
    int height = heightProp.cast<int>();
    WindowManager::Instance()->updateWindowSize(width, height);
    WindowManager::Instance()->setTitle(title);
}

void ScriptManager::loadTIEntityDefinitions(LuaRef tientityDefinitions) {
    
}
