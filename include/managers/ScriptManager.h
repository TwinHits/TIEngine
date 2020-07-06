#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include "templates/Singleton.h"

#include <array>
#include <string>
#include <vector>

#include "objects/entities/TIEntity.h"
#include "utilities/LuaHelpers.h"

namespace TIE {

class ScriptManager : public Singleton<ScriptManager> {
	public:
		ScriptManager();
		~ScriptManager() {};

		void loadScript(const std::string& scriptName);

	private:
		lua_State* luaState;

		void loadWindowProperties(const luabridge::LuaRef&);
		void loadTIEntities(const std::vector<std::string>&);
		void loadTIEntity(const std::string&, const luabridge::LuaRef&, TIEntity* parent);

		//Schema, lets see how big it gets before moving it to a new home
		std::array<std::string, 3> TIENTITY_COMPONENTS = { "drawn", "moves", "collides" };

		ScriptManager(const ScriptManager&);
		void operator=(const ScriptManager&) {};
};

}
#endif
