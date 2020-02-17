#include <iostream>
#include <string>

#include "managers/ConfigManager.h"
#include "managers/LogManager.h"
#include "managers/ScriptManager.h"

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

    LuaRef t = getGlobal(this->luaState, "window");
}
