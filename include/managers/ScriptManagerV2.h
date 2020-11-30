#ifndef SCRIPTMANAGER_V2_H
#define SCRIPTMANAGER_V2_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <sol/sol.hpp>

#include <map>
#include <string>

#include "objects/GlobalId.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"

namespace TIE {

class ScriptManager : public Singleton<ScriptManager>, Manager {
public:
	bool initialize();
	void loadScript(const std::string&);
	TIEntityFactory& loadTIEntityDefinition(const std::string&, const sol::table&);
	void runFunction(const GlobalId, TIEntity&);

    void setScriptWorkingDirectory(const std::string&);
    const std::string& getScriptWorkingDirectory();

	ScriptManager() {};
	~ScriptManager() {};

private:
	sol::state luaState;
	std::string scriptWorkingDirectory = "";
	std::map<GlobalId, sol::function> functions;

	TIEntityFactory& loadTIEntityDefinition(const std::string&, const sol::table&, TIEntityFactory*);
	TIEntityFactory& getFactory(const std::string&, TIEntityFactory*);
	void readComponentValues(TIEntityFactory&, const std::string&, const sol::table&);

	ScriptManager(const ScriptManager&);
	void operator=(const ScriptManager&) {};
};

}
#endif
