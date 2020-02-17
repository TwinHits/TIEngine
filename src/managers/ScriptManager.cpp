#include <iostream>
#include <string>
  
//Lua headers must be included before LuaBridge
extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}
#include <LuaBridge.h>

#include "managers/ConfigManager.h"
#include "managers/LogManager.h"
#include "managers/ScriptManager.h"

using namespace luabridge;
using namespace TIE;

ScriptManager::ScriptManager() {
	
}


ScriptManager::~ScriptManager() {

}

void ScriptManager::loadScript() {

	auto scriptsPath = ConfigManager::Instance()->getScriptsPath();
	std::string script = scriptsPath + "script.lua";

    lua_State* L = luaL_newstate();
    luaL_dofile(L, script.c_str());
    luaL_openlibs(L);
    lua_pcall(L, 0, 0, 0);
    LuaRef s = getGlobal(L, "testString");
    LuaRef n = getGlobal(L, "number");
    std::string luaString = s.cast<std::string>();
    int answer = n.cast<int>();
    LogManager::Instance()->logInfo(luaString);
}
