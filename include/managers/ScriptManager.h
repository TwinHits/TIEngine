#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <array>
#include <string>
#include <vector>

#include "objects/entities/TIEntity.h"
#include "utilities/LuaHelpers.h"

namespace TIE {

class ScriptManager : public Singleton<ScriptManager>, Manager {
	public:
		bool initialize();
		void loadScript(const std::string& scriptName);

		ScriptManager() {};
		~ScriptManager() {};

	private:
		lua_State* luaState = nullptr;

		void loadSettings(const luabridge::LuaRef&);
		void loadWindowProperties(const luabridge::LuaRef&);
		void loadTIEntities(const std::vector<std::string>&);
		void loadTIEntity(const std::string&, const luabridge::LuaRef&, TIEntity* parent);

		ScriptManager(const ScriptManager&);
		void operator=(const ScriptManager&) {};
};

}
#endif
