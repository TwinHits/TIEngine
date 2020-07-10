#ifndef STARTUPMANAGER_H
#define STARTUPMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

namespace TIE {

class StartUpManager : public Singleton<StartUpManager>, Manager {
	public:
		StartUpManager() {};
		~StartUpManager() {};

		bool initialize();

	private:
		bool initialized = false;
};

} 
#endif