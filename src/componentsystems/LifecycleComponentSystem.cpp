#include "componentsystems/LifecycleComponentSystem.h" 

#include <string>

#include "managers/LogManager.h" 
#include "managers/ScriptManager.h"
#include "objects/components/LifecycleComponent.h"
#include "utils/ComponentSystems.h"

using namespace TIE;

void LifecycleComponentSystem::update(const float delta) {
	for (auto& c : this->components) {
		if (c.lifecycleComponent.updatedFunctionId) {
			this->runFunction(c.lifecycleComponent.updatedFunctionId, c.tientity);
		}
	}
}


void LifecycleComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
	GlobalId createdFunctionId = 0;
	if (factory.functionValues.count(LifecycleComponentSystem::CREATED)) {
		createdFunctionId = factory.functionValues.at(LifecycleComponentSystem::CREATED);
	}

	GlobalId updatedFunctionId = 0;
	if (factory.functionValues.count(LifecycleComponentSystem::UPDATED)) {
		updatedFunctionId = factory.functionValues.at(LifecycleComponentSystem::UPDATED);
	}

	GlobalId removedFunctionId = 0;
	if (factory.functionValues.count(LifecycleComponentSystem::REMOVED)) {
		removedFunctionId = factory.functionValues.at(LifecycleComponentSystem::REMOVED);
	}

	if (createdFunctionId || updatedFunctionId || removedFunctionId) {
		LifecycleComponent& lifecycleComponent = tientity.addComponent<LifecycleComponent>();
		Components components = { tientity, lifecycleComponent };

		lifecycleComponent.createdFunctionId = createdFunctionId;
		lifecycleComponent.updatedFunctionId = updatedFunctionId;
		lifecycleComponent.removedFunctionId = removedFunctionId;

		this->components.push_back(components);
	}
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


const std::string& LifecycleComponentSystem::getName() {
	return LifecycleComponentSystem::LIFECYCLE;
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
		ScriptManager::Instance()->runFunction<bool>(functionId, tientity);
	}
}
