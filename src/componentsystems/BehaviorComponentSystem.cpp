#include "componentsystems\BehaviorComponentSystem.h"

#include "managers/ScriptManager.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"

using namespace TIE;

void BehaviorComponentSystem::update(const float) {
	for (Components& components : this->components) {
        if (components.behaviorComponent.behaviorFunctionId) {
            ScriptManager::Instance()->runFunction<bool>(components.behaviorComponent.behaviorFunctionId, components.tientity);
        }
	}
}


void BehaviorComponentSystem::addComponent(const TIEntityFactory& tientityFactory, TIEntity& tientity) {
    BehaviorComponent& behaviorComponent = tientity.addComponent<BehaviorComponent>();
    Components components = { tientity, behaviorComponent };
    this->components.push_back(components);

    behaviorComponent.behaviorFunctionId = tientityFactory.functionValues.at(BehaviorComponentSystem::BEHAVIOR);
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


void BehaviorComponentSystem::setBehavior(TIEntity& tientity, GlobalId functionId) {
    BehaviorComponent* behaviorComponent = tientity.getComponent<BehaviorComponent>();
    if (behaviorComponent != nullptr) {
        behaviorComponent->behaviorFunctionId = functionId;
    }
}


void BehaviorComponentSystem::setBehavior(TIEntity& tientity, const std::string& name) {
    GlobalId functionId = ScriptManager::Instance()->getFunctionIdByName(name);
    this->setBehavior(tientity, functionId);
}

