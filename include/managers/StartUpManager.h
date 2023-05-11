#ifndef STARTUPMANAGER_H
#define STARTUPMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

namespace TIE {

class StartUpManager : public Singleton<StartUpManager>, public Manager {
	public:
		StartUpManager() {};
		~StartUpManager() {};

		void initialize();

	private:
		bool initialized = false;
};

} 
#endif