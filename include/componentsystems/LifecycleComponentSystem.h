#ifndef LIFECYCLECOMPONENTSYSTEM_H
#define LIFECYCLECOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include "objects/components/LifecycleComponent.h"

namespace TIE {

class LifecycleComponentSystem : public Singleton<LifecycleComponentSystem>, public ComponentSystem {
public:
	LifecycleComponentSystem() {};
	void update(const float);
	void addComponent(const TIEntityFactory&, TIEntity&);
	bool removeComponent(TIEntity&);
	const std::string& getName();

    bool setComponentProperty(const std::string&, bool, TIEntity&);
    bool setComponentProperty(const std::string&, float, TIEntity&);
    bool setComponentProperty(const std::string&, const std::string&, TIEntity&);
	sol::object getComponentProperty(const std::string&, TIEntity&);
	ComponentSystems::ComponentSystemPropertiesMap& populateComponentSystemsPropertiesMap(ComponentSystems::ComponentSystemPropertiesMap&);

	void runCreated(TIEntity& tientity);
	void runRemoved(TIEntity& tientity);

	static const inline std::string LIFECYCLE = "lifecycle";
	static const inline std::string CREATED = "lifecycle.created";
	static const inline std::string UPDATED = "lifecycle.updated";
	static const inline std::string REMOVED = "lifecycle.removed";
private:
	struct Components {
		TIEntity& tientity;
		LifecycleComponent& lifecycleComponent;
	};
	std::list<Components> components;

	void runFunction(GlobalId, TIEntity&);
};

}
#endif