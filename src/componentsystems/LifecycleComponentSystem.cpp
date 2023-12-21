#include "componentsystems/LifecycleComponentSystem.h" 

#include <sol/sol.hpp>

#include <string>

#include "managers/ComponentSystemsManager.h"
#include "managers/LogManager.h" 
#include "managers/ScriptManager.h"
#include "objects/components/LifecycleComponent.h"
#include "utils/ComponentSystems.h"

using namespace TIE;

LifecycleComponentSystem::LifecycleComponentSystem() {
	this->setName(LifecycleComponentSystem::LIFECYCLE);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(LifecycleComponentSystem::CREATED, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(LifecycleComponentSystem::REMOVED, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(LifecycleComponentSystem::UPDATED, this);
}


void LifecycleComponentSystem::update(const float delta) {
	for (auto& c : this->components) {
		if (c.lifecycleComponent.updatedFunctionId) {
			this->runFunction(c.lifecycleComponent.updatedFunctionId, c.tientity);
		}
	}
}


LifecycleComponent& LifecycleComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<LifecycleComponent>()) {
		LifecycleComponent& lifecycleComponent = tientity.addComponent<LifecycleComponent>();
		this->components.push_back({ tientity, lifecycleComponent });
		return lifecycleComponent;
	} else {
		return *tientity.getComponent<LifecycleComponent>();
	}
}


LifecycleComponent& LifecycleComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
	LifecycleComponent& lifecycleComponent = this->addComponent(tientity);
	const ScriptTableReader& reader = factory.getReader().getReader(LifecycleComponentSystem::LIFECYCLE);

	GlobalId createdFunctionId = reader.get<GlobalId>(LifecycleComponentSystem::CREATED, lifecycleComponent.createdFunctionId);
    lifecycleComponent.createdFunctionId = createdFunctionId;

	GlobalId updatedFunctionId = reader.get<GlobalId>(LifecycleComponentSystem::UPDATED, lifecycleComponent.updatedFunctionId);
    lifecycleComponent.updatedFunctionId = updatedFunctionId;

	GlobalId removedFunctionId = reader.get<GlobalId>(LifecycleComponentSystem::REMOVED, lifecycleComponent.removedFunctionId);
    lifecycleComponent.removedFunctionId = removedFunctionId;

	return lifecycleComponent;
}


bool LifecycleComponentSystem::removeComponent(TIEntity& tientity) {
	LifecycleComponent* lifecycleComponent = tientity.getComponent<LifecycleComponent>();
	if (lifecycleComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->lifecycleComponent == lifecycleComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<LifecycleComponent>();
	} else {
		return false;
	}
}


void LifecycleComponentSystem::runCreated(TIEntity& tientity) {
	LifecycleComponent* lifecycleComponent = tientity.getComponent<LifecycleComponent>();
	if (lifecycleComponent != nullptr) {
		this->runFunction(lifecycleComponent->createdFunctionId, tientity);
	}
}


void LifecycleComponentSystem::runRemoved(TIEntity& tientity) {
	LifecycleComponent* lifecycleComponent = tientity.getComponent<LifecycleComponent>();
	if (lifecycleComponent != nullptr) {
		this->runFunction(lifecycleComponent->removedFunctionId, tientity);
	}
}


void LifecycleComponentSystem::runFunction(GlobalId functionId, TIEntity& tientity) {
	if (functionId) {
		ScriptManager::Instance()->runFunction<sol::optional<bool> >(functionId, tientity);
	}
}
