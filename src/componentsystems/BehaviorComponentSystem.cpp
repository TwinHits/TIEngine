#include "componentsystems\BehaviorComponentSystem.h"

#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"

using namespace TIE;

const std::string BehaviorComponentSystem::BEHAVIORS = "behaviors";
const std::string BehaviorComponentSystem::BEHAVIOR = "behaves.behavior";
const std::string BehaviorComponentSystem::BEHAVES = "behaves";

void BehaviorComponentSystem::update(const float) {

}


void BehaviorComponentSystem::addComponent(const TIEntityFactory& tientityFactory, TIEntity& tientity) {
	BehaviorComponent& behaviorComponent = tientity.addComponent<BehaviorComponent>();
	Components components = { tientity, behaviorComponent };

	if (tientityFactory.stringValues.count(BehaviorComponentSystem::BEHAVIOR)) {
		std::string behavior = tientityFactory.stringValues.at(BehaviorComponentSystem::BEHAVIOR);
		behaviorComponent.behavior = behavior;
	}
}
