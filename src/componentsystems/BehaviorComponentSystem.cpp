#include "componentsystems\BehaviorComponentSystem.h"

#include "managers/ScriptManagerV2.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"

using namespace TIE;

void BehaviorComponentSystem::update(const float) {
	for (Components& components : this->components) {
		ScriptManager::Instance()->runFunction(components.behaviorComponent.behaviorFunctionId, components.tientity);
	}
}


void BehaviorComponentSystem::addComponent(const TIEntityFactory& tientityFactory, TIEntity& tientity) {
	if (tientityFactory.functionValues.count(BehaviorComponentSystem::BEHAVIOR)) {
        BehaviorComponent& behaviorComponent = tientity.addComponent<BehaviorComponent>();
        Components components = { tientity, behaviorComponent };

		behaviorComponent.behaviorFunctionId = tientityFactory.functionValues.at(BehaviorComponentSystem::BEHAVIOR);
		this->components.push_back(components);
	}
}


const std::string& BehaviorComponentSystem::getName() {
    return BehaviorComponentSystem::BEHAVES;
}

