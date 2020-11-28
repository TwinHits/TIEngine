#ifndef SCRIPTMANAGER_V2_H
#define SCRIPTMANAGER_V2_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <sol/sol.hpp>

#include <string>

#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"

namespace TIE {

class ScriptManagerV2 : public Singleton<ScriptManagerV2>, Manager {
public:
	bool initialize();
	void loadScript(const std::string&);
	TIEntityFactory& loadTIEntityDefinition(const std::string&, const sol::table&);

	ScriptManagerV2() {};
	~ScriptManagerV2() {};

private:
	sol::state luaState;

	TIEntityFactory& loadTIEntityDefinition(const std::string&, const sol::table&, TIEntityFactory*);
	TIEntityFactory& getFactory(const std::string&, TIEntityFactory*);
	void readComponentValues(TIEntityFactory&, const std::string&, const sol::table&);

	void registerTIEntityInterface();
	void registerTIEngineInterface();

	ScriptManagerV2(const ScriptManagerV2&);
	void operator=(const ScriptManagerV2&) {};
};

}
#endif
