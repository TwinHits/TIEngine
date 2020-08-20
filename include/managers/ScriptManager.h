#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <string>
#include <vector>

#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "utils/LuaHelpers.h"

namespace TIE {

class ScriptManager : public Singleton<ScriptManager>, Manager {
	public:
		bool initialize();
		void loadScript(const std::string& scriptName);

		ScriptManager() {};
		~ScriptManager() {};

	private:
		lua_State* luaState = nullptr;

		void loadAssets(const luabridge::LuaRef&, const std::string&);
		void loadWindowProperties(const luabridge::LuaRef&);
		TIEntity* loadGrid(const luabridge::LuaRef&);

		void loadTIEntities(const std::vector<std::string>&, TIEntity*);
		void loadTIEntity(const std::string&, const luabridge::LuaRef&, TIEntity*);
		void readComponentValues(TIEntityFactory&, const std::string&, const luabridge::LuaRef&, const std::string&);

		ScriptManager(const ScriptManager&);
		void operator=(const ScriptManager&) {};
};

}
#endif
