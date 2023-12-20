#ifndef LIFECYCLECOMPONENTSYSTEM_H
#define LIFECYCLECOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include "objects/components/LifecycleComponent.h"

namespace TIE {

class LifecycleComponentSystem : public Singleton<LifecycleComponentSystem>, public OwnsComponent<LifecycleComponent> {
public:
	LifecycleComponentSystem();
	void update(const float);
	LifecycleComponent& addComponent(TIEntity&);
	LifecycleComponent& addComponent(const TIEntityFactory&, TIEntity&);
	bool removeComponent(TIEntity&);

	void runCreated(TIEntity& tientity);
	void runRemoved(TIEntity& tientity);

	static const inline std::string LIFECYCLE = "lifecycle";
	static const inline std::string CREATED = "created";
	static const inline std::string UPDATED = "updated";
	static const inline std::string REMOVED = "removed";
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