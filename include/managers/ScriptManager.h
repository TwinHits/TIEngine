#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include "templates/Singleton.h"

#include <string>
#include <vector>

#include "utilities/LuaHelpers.h"

namespace TIE {

class ScriptManager : public Singleton<ScriptManager> {
	public:
		ScriptManager();
		~ScriptManager() {};

		void loadScript(const std::string& scriptName);

	private:
		lua_State* luaState;

		void loadWindowProperties(std::vector<std::string>);
		void loadTIEntityDefinitions(std::vector<std::string>);

		ScriptManager(const ScriptManager&);
		void operator=(const ScriptManager&) {};
};

}
#endif
