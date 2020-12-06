#include "componentsystems\BehaviorComponentSystem.h"

#include "managers/ScriptManagerV2.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"

using namespace TIE;

void BehaviorComponentSystem::update(const float) {
	for (Components& components : this->components) {
		ScriptManager::Instance()->runFunction<bool>(components.behaviorComponent.behaviorFunctionId, components.tientity);
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

bool BehaviorComponentSystem::removeComponent(TIEntity& tientity) {
    BehaviorComponent* behaviorComponent = tientity.getComponent<BehaviorComponent>();
    if (behaviorComponent != nullptr) {
        for (auto i = this->components.begin(); i != this->components.end(); ++i) {
            if (&i->behaviorComponent == behaviorComponent) {
                this->components.erase(i);
                break;
            }
        }
        return tientity.removeComponent<BehaviorComponent>();
    } else {
        return false;
    }
}


const std::string& BehaviorComponentSystem::getName() {
    return BehaviorComponentSystem::BEHAVES;
}

