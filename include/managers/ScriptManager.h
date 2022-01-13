#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <sol/sol.hpp>

#include <map>
#include <string>

#include "interfaces/TIEngineInterface.h"
#include "interfaces/TIEntityInterface.h"
#include "objects/GlobalId.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"

namespace TIE {

class ScriptManager : public Singleton<ScriptManager>, Manager {
public:
	bool initialize();
	void loadScript(const std::string&);
	TIEntityFactory& loadTIEntityDefinition(TIEntityFactory&, const sol::table&);

	template <typename T>
	T runFunction(const GlobalId functionId, TIEntity& tientity) {
        TIEntityInterface tientityInterface(tientity);
        TIEngineInterface engineInterface = TIEngineInterface();
		return this->functions.at(functionId)(std::tuple<TIEntityInterface, TIEngineInterface>(tientityInterface, engineInterface));
	}
	template <> void runFunction<void>(const GlobalId, TIEntity&);

	template <typename T>
	T runFunction(const std::string& name, TIEntity& tientity) {
        TIEntityInterface tientityInterface(tientity);
        TIEngineInterface engineInterface = TIEngineInterface();
		return this->getFunctionByName(name)(std::tuple<TIEntityInterface, TIEngineInterface>(tientityInterface, engineInterface));
	}
	template <> void runFunction<void>(const std::string&, TIEntity&);

	GlobalId registerFunctionByName(const std::string&, const sol::function&);
	GlobalId getFunctionIdByName(const std::string&);

    void setScriptWorkingDirectory(const std::string&);
    const std::string& getScriptWorkingDirectory();

	sol::table getNewTable();

	ScriptManager() {};
	~ScriptManager() {};

private:
	sol::state luaState;
	std::string scriptWorkingDirectory = "";
	std::map<GlobalId, sol::function> functions;
	std::map<std::string, GlobalId> functionsByName;

	void readComponentValues(TIEntityFactory&, const std::string&, const sol::table&);
	const sol::function& getFunctionByName(const std::string&);
	bool isValidDefinitionFieldName(const std::string&);

	ScriptManager(const ScriptManager&);
	void operator=(const ScriptManager&) {};
};

}
#endif
