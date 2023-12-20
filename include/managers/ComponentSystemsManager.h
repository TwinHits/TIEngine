#ifndef COMPONENTSYSTEMSMANAGER_H
#define COMPONENTSYSTEMSMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <map>
#include <string>
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

		void registerComponentPropertyKey(const std::string&, ComponentSystem*);
		ComponentSystem* getComponentSystemForKey(const std::string&);

		void updateComponentSystems(const float);

		void removeComponents(TIEntity&);

		ComponentSystemsManager() {};
		~ComponentSystemsManager() {};
	private:
		std::vector<ComponentSystem*> componentSystems;
		std::map<std::string, ComponentSystem*> componentNamesToComponentSystems;
		ComponentSystems::ComponentSystemPropertiesMap componentSystemPropertiesMap;

		std::map<std::string, ComponentSystem*> componentSystemByPropertyKey;

		ComponentSystemsManager(const ComponentSystemsManager&);
		void operator=(const ComponentSystemsManager&) {};
};

}
#endif
