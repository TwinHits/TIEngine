#include "utilities/LuaHelpers.h"

#include <string>

#include "managers/LogManager.h"

// https://eliasdaler.wordpress.com/2015/09/08/using-lua-with-cpp-in-practice-part-2/

bool TIE::Lua::loadScript(lua_State* L, const std::string& script) {

    int errorCode = luaL_loadfile(L, script.c_str()); //success == false
    if (errorCode == 0) {
        LogManager::Instance()->info("Loaded script " + script);
        errorCode = lua_pcall(L, 0, 0, 0);  //success == false
        if (errorCode == 0) {
            LogManager::Instance()->debug("Called global lua function for " + script);
        } else {
            LogManager::Instance()->error("Could not call global lua function for " + script + ": " + std::to_string(errorCode));
            return false;
        }
	} else if (errorCode == 7) {
        LogManager::Instance()->error("Could not load lua script " + script + ": Could not find file.");
        return false;
    } else if (errorCode == 3) {
        LogManager::Instance()->error("Could not load lua script " + script + ": Syntax error.");
        return false;
    } else {
        LogManager::Instance()->error("Could not load lua script " + script + ": Error Code " + std::to_string(errorCode));
        return false;
    }
    return true;
}


//Gets Lua table by dot notation
void TIE::Lua::lua_gettostack(lua_State* L, const std::string& variableName) {
    int level = 0;
    std::string var = "";
    for (unsigned int i = 0; i < variableName.size(); i++) {
        //Add check for dot before iterating, then substring to get the parts, then iterate through parts for levels
        if (variableName.at(i) == '.') {
            if (level == 0) {
                lua_getglobal(L, var.c_str());
            } else {
                lua_getfield(L, -1, var.c_str());
            }
 
            if (lua_isnil(L, -1)) {
                LogManager::Instance()->error("Can't get " + variableName + " from Lua script");
                return;
            } else {
                var = "";
                level++;
            }
        } else {
            var += variableName.at(i);
        }
    }
    if (level == 0) {
        lua_getglobal(L, var.c_str());
    } else {
        lua_getfield(L, -1, var.c_str());
    }

    if (level == 0) { return; } // no need to remove anything
 
    int tableIndex = lua_gettop(L) - level;
    lua_replace(L, tableIndex);
    lua_settop(L, tableIndex);
}


void TIE::Lua::loadGetKeysFunction(lua_State* L) {
    std::string code =
        R"(function getKeys(t)
        s = {}
        for k, v in pairs(t) do
            table.insert(s, k)
            end 
        return s 
        end)";
    luaL_dostring(L, code.c_str());
}


std::vector<std::string> TIE::Lua::getTableKeys(lua_State* L, const std::string& name) {
    lua_getglobal(L, "getKeys"); // get function
    if (lua_isnil(L, -1)) {
        LogManager::Instance()->debug("Lua getKeys function is not loaded yet. Loading...");
        loadGetKeysFunction(L);
        lua_getglobal(L, "getKeys");
        if (lua_isnil(L, -1)) {
            LogManager::Instance()->error("Failed to load Lua getKeys function.");
        }
    }

    lua_gettostack(L, name);
    std::vector<std::string> keys;
    int errorCode = lua_pcall(L, 1, 1, 0); //success == false
    if (errorCode == 2) {
        LogManager::Instance()->error("Could not find lua table key: " + name);
        return keys;
    } else if (errorCode != 0) {
        LogManager::Instance()->error("Failed to call lua getKeys function: " + std::to_string(errorCode));
        return keys;
    }

    lua_pushnil(L); //Magic sauce for some reason
    while (lua_next(L, -2)) { // get values one by one
		if (lua_type(L, -1) == LUA_TSTRING) { // check if key is a string
			keys.push_back(lua_tostring(L, -1));
		}
		lua_pop(L, 1);
    }

    lua_settop(L, 0); // remove s table from stack 
    return keys;
}


std::string TIE::Lua::getString(const std::string& key, const luabridge::LuaRef& table) {
    luabridge::LuaRef luaRef = table[key];
    std::string value = luaRef.cast<std::string>();
    return value;
}


bool TIE::Lua::getBool(const std::string& key, const luabridge::LuaRef& table) {
    luabridge::LuaRef luaRef = table[key];
    bool value = luaRef.cast<bool>();
    return value;
}


float TIE::Lua::getFloat(const std::string& key, const luabridge::LuaRef& table) {
    luabridge::LuaRef luaRef = table[key];
    float value = luaRef.cast<float>();
    return value;
}
