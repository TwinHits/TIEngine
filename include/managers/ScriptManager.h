#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <sol/sol.hpp>

#include <map>
#include <string>

#include "interfaces/TIEngineInterface.h"
#include "interfaces/TIEntityInterface.h"
#include "interfaces/MessageInterface.h"
#include "interfaces/ai/FiniteStateMachineInterface.h"
#include "objects/GlobalId.h"
#include "objects/tientities/TIEntity.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "objects/factories/ai/FiniteStateMachineFactory.h"

namespace TIE {

class ScriptManager : public Singleton<ScriptManager>, public Manager {
public:
	void initialize();

	void loadScript(const std::string&);

	const GlobalId registerFunction(const sol::function&);

	FiniteStateMachineFactory& loadFiniteStateMachineDefinition(FiniteStateMachineFactory&, const sol::table&);

	template <typename T>
	T runFunction(const GlobalId functionId, TIEntity& tientity) {
        TIEntityInterface tientityInterface(tientity);
		return this->functions.at(functionId)(std::tuple<TIEntityInterface>(tientityInterface));
	}

	template <typename T>
	T runFunction(const GlobalId functionId, FiniteStateMachine& finiteStateMachine, const float delta) {
        TIEntityInterface tientityInterface(finiteStateMachine.getTIEntity());
		FiniteStateMachineInterface finiteStateMachineInterface(finiteStateMachine);
		return this->functions.at(functionId)(std::tuple<TIEntityInterface, FiniteStateMachineInterface, const float>(tientityInterface, finiteStateMachineInterface, delta));
	}

	template <typename T>
	T runFunction(const GlobalId functionId, TIEntity& tientity, const float delta) {
		TIEntityInterface tientityInterface(tientity);
		return this->functions.at(functionId)(std::tuple<TIEntityInterface, const float>(tientityInterface, delta));
	}

	template <typename T>
	T runFunction(const GlobalId functionId, FiniteStateMachine& finiteStateMachine, const sol::object payload) {
		TIEntityInterface tientityInterface(finiteStateMachine.getTIEntity());
		FiniteStateMachineInterface finiteStateMachineInterface(finiteStateMachine);
		return this->functions.at(functionId)(std::tuple<TIEntityInterface, FiniteStateMachineInterface, const sol::object>(tientityInterface, finiteStateMachineInterface, payload));
	}

	template <typename T>
	T runFunction(const GlobalId functionId, FiniteStateMachine& finiteStateMachine, Message& message) {
		TIEntityInterface tientityInterface(finiteStateMachine.getTIEntity());
		FiniteStateMachineInterface finiteStateMachineInterface(finiteStateMachine);
		MessageInterface messageInterface(message);
		return this->functions.at(functionId)(std::tuple<TIEntityInterface, FiniteStateMachineInterface, MessageInterface>(tientityInterface, finiteStateMachineInterface, messageInterface));
	}

	template <typename T>
	T runFunction(const GlobalId functionId, TIEntity& tientity, Message& message) {
		TIEntityInterface tientityInterface(tientity);
		MessageInterface messageInterface(message);
		return this->functions.at(functionId)(std::tuple<TIEntityInterface, MessageInterface>(tientityInterface, messageInterface));
	}

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

	bool isValidDefinitionFieldName(const std::string&);

	ScriptManager(const ScriptManager&);
	void operator=(const ScriptManager&) {};
};

}
#endif
