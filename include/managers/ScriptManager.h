#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

//Lua headers must be included before LuaBridge
extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}
#include <LuaBridge.h>

#include "templates/Singleton.h"


namespace TIE {

class ScriptManager : public Singleton<ScriptManager> {
	public:
		ScriptManager();
		~ScriptManager();

		void loadScript(const std::string& scriptName);

	private:

		lua_State* luaState;

		ScriptManager(const ScriptManager&);
		void operator=(const ScriptManager&);
};

}
#endif
