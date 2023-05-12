#ifndef COMPONENTSYSTEMSMANAGER_H
#define COMPONENTSYSTEMSMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <map>
#include <vector>

#include "componentsystems/ComponentSystem.h"

namespace TIE {

	class ComponentSystemsManager : public Singleton<ComponentSystemsManager>, public Manager {
	public:
		void initialize();

		const std::vector<ComponentSystem*>& getComponentSystems();
		bool isValidComponentName(const std::string&);
		ComponentSystem* getComponentSystemByComponentName(const std::string&);
		const ComponentSystems::ComponentSystemPropertiesMap& getComponentSystemPropertiesMap();

		void updateComponentSystems(const float);

		void removeComponents(TIEntity&);

		ComponentSystemsManager() {};
		~ComponentSystemsManager() {};
	private:
		std::vector<ComponentSystem*> componentSystems;
		std::map<std::string, ComponentSystem*> componentNamesToComponentSystems;
		ComponentSystems::ComponentSystemPropertiesMap componentSystemPropertiesMap;

		ComponentSystemsManager(const ComponentSystemsManager&);
		void operator=(const ComponentSystemsManager&) {};
};

}
#endif
