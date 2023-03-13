#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <sol/sol.hpp>

#include <map>
#include <string>

#include "interfaces/TIEngineInterface.h"
#include "interfaces/TIEntityInterface.h"
#include "interfaces/ai/FiniteStateMachineInterface.h"
#include "objects/GlobalId.h"
#include "objects/tientities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/factories/ai/FiniteStateMachineFactory.h"

namespace TIE {

class ScriptManager : public Singleton<ScriptManager>, Manager {
public:
	bool initialize();

	void loadScript(const std::string&);
	TIEntityFactory& loadTIEntityDefinition(TIEntityFactory&, const sol::table&);
	FiniteStateMachineFactory& loadFiniteStateMachineDefinition(FiniteStateMachineFactory&, const sol::table&);

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

	template <typename T>
	T runFunction(const GlobalId functionId, FiniteStateMachine& finiteStateMachine) {
        TIEntityInterface tientityInterface(finiteStateMachine.getTIEntity());
		FiniteStateMachineInterface finiteStateMachineInterface(finiteStateMachine);
		return this->functions.at(functionId)(std::tuple<TIEntityInterface, FiniteStateMachineInterface>(tientityInterface, finiteStateMachineInterface));
	}
	template <> void runFunction<void>(const GlobalId, FiniteStateMachine&);

	GlobalId registerFunctionByName(const std::string&, const sol::function&);
	GlobalId getFunctionIdByName(const std::string&);

    void setScriptWorkingDirectory(const std::string&);
    const std::string& getScriptWorkingDirectory();

	sol::table getNewTable();

    template <typename T>
	T getValueFromObject(const sol::object& object) {
		return object.as<T>();
	}

	template <typename T>
	sol::object getObjectFromValue(T value) {
		return sol::make_object<T>(this->luaState, value);
	}

	std::string getStringFromObject(const sol::object&);
	sol::table copyTable(const sol::table&);

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
