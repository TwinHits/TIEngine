#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include "templates/Singleton.h"

namespace TIE {

class ScriptManager : public Singleton<ScriptManager> {
	public:
		ScriptManager();
		~ScriptManager();

		void loadScript();

	private:

		ScriptManager(const ScriptManager&);
		void operator=(const ScriptManager&);
};

}
#endif
