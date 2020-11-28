#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include <string>

#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"

namespace TIE {

class ScriptManager : public Singleton<ScriptManager>, Manager {
public:
	bool initialize();
	void loadScript(const std::string&);
	void runFunction(const std::string&, TIEntity&);

	ScriptManager() {};
	~ScriptManager() {};

private:
	sol::state luaState;
	std::map<std::string, sol::function> functions;

	void loadWorld(const sol::table&);

	ScriptManager(const ScriptManager&);
	void operator=(const ScriptManager&) {};
};

}
#endif
