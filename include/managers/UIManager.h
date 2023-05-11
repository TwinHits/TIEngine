#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include "objects/tientities/TIEntity.h"

namespace TIE {

	class UIManager : public Singleton<UIManager>, public Manager {
	public:
		void initialize();

		void updateEngineEntities(const float);
		void updateEngineEntities(TIEntity&, const float);

		UIManager() {};
		~UIManager() {};
	private:
		UIManager(const UIManager&);
		void operator=(const UIManager&) {};
};

}
#endif
