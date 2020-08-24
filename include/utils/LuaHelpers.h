#ifndef LUAHELPERS_H
#define LUAHELPERS_H

#include <string>
#include <vector>

//Lua headers must be included before LuaBridge
extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}
#include <LuaBridge.h>

namespace TIE {
	namespace Lua {
		bool loadScript(lua_State* L, const std::string& filename); // will be explained later
		void lua_gettostack(lua_State* L, const std::string& variableName); // ...and this one
		void loadGetKeysFunction(lua_State* L);
		std::vector<std::string> getTableKeys(lua_State* L, const std::string& name);

		std::vector<std::string>& getVector(const luabridge::LuaRef&, std::vector<std::string>&);

		std::string getString(const std::string&, const luabridge::LuaRef&);
		bool getBool(const std::string&, const luabridge::LuaRef&);
		float getFloat(const std::string&, const luabridge::LuaRef&);
	}
}
#endif