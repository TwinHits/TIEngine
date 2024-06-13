#include "componentsystems/BehavesComponentSystem.h" 

#include <string>
#include <vector>

#include "interfaces/ai/FiniteStateMachineInterface.h"
#include "managers/ComponentSystemsManager.h"
#include "managers/MessageManager.h"
#include "managers/WorldManager.h"
#include "objects/constants/MessageSubscriptions.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "objects/factories/ai/FiniteStateMachineFactory.h"
#include "objects/factories/ai/BehaviorTreeNodeFactory.h"
#include "objects/tientities/TIEntity.h"
#include "utils/ComponentSystems.h"
#include "utils/types/ComponentSystemsTypes.h"

using namespace TIE;

BehavesComponentSystem::BehavesComponentSystem() {
	this->setName(BehavesComponentSystem::BEHAVES);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(BehavesComponentSystem::ROOT_BEHAVIOR_TREE_NODE, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(BehavesComponentSystem::ROOT_FINITE_STATE_MACHINE, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(BehavesComponentSystem::ROOT_PAYLOAD, this);

	this->initializeBehaviorTreeNodeTypes();
	this->initializeBehaviorTreeDecoratorTypes();
	this->initializeBehaviorTreeNodeStatuses();
	this->initializeBehaviorTreeNodeStatusMessageSubscriptions();
}


void BehavesComponentSystem::update(const float delta) {
	for (auto& c : components) {
		if (c.behavesComponent.rootFiniteStateMachine) {
			c.behavesComponent.rootFiniteStateMachine->update(delta);
		}
		if (c.behavesComponent.rootBehaviorTreeNode) {
			c.behavesComponent.rootBehaviorTreeNode->update(delta);
		}
	}
}


BehavesComponent& BehavesComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<BehavesComponent>()) {
        BehavesComponent& behavesComponent = tientity.addComponent<BehavesComponent>();
        this->components.push_back({ behavesComponent });
        return behavesComponent;
	} else {
		return *tientity.getComponent<BehavesComponent>();
	}
}


BehavesComponent& BehavesComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
    BehavesComponent& component = this->addComponent(tientity);
	const ScriptTableReader& reader = factory.getReader().getReader(BehavesComponentSystem::BEHAVES);

	const GlobalId& rootPayload = reader.get<float>(BehavesComponentSystem::ROOT_PAYLOAD, component.rootPayload);
	this->setComponentProperty(BehavesComponentSystem::ROOT_PAYLOAD, rootPayload, tientity);

	const GlobalId& rootFiniteStateMachineId = reader.get<float>(BehavesComponentSystem::ROOT_FINITE_STATE_MACHINE, 0);
	this->setComponentProperty(BehavesComponentSystem::ROOT_FINITE_STATE_MACHINE, rootFiniteStateMachineId, tientity);

	const GlobalId& rootBehaviorTreeNodeId = reader.get<float>(BehavesComponentSystem::ROOT_BEHAVIOR_TREE_NODE, 0);
	this->setComponentProperty(BehavesComponentSystem::ROOT_BEHAVIOR_TREE_NODE, rootBehaviorTreeNodeId, tientity);

	return component;
}


bool BehavesComponentSystem::removeComponent(TIEntity& tientity) {
	BehavesComponent* behavesComponent = tientity.getComponent<BehavesComponent>();
	if (behavesComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->behavesComponent == behavesComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<BehavesComponent>();
	} else {
		return false;
	}
}


void BehavesComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity)  {
    BehavesComponent& component = this->addComponent(tientity);
	if (key == BehavesComponentSystem::ROOT_PAYLOAD) {
		component.rootPayload = value;
	} else if (key == BehavesComponentSystem::ROOT_BEHAVIOR_TREE_NODE) {
		BehaviorTreeNodeFactory* factory = WorldManager::Instance()->getBehaviorTreeNodeFactory(value);
		if (factory) {
			component.rootBehaviorTreeNode = std::move(factory->build(tientity));
		}
	} else if (key == BehavesComponentSystem::ROOT_FINITE_STATE_MACHINE) {
		FiniteStateMachineFactory* factory = WorldManager::Instance()->getFiniteStateMachineFactory(value);
		if (factory) {
			if (component.rootFiniteStateMachine) {
				component.rootFiniteStateMachine->onExit();
			}
			component.rootFiniteStateMachine = std::move(factory->build(tientity));
			component.rootFiniteStateMachine->onEnter(ScriptManager::Instance()->getObjectFromValue(component.rootPayload));
		}
    }
}


sol::object BehavesComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
	BehavesComponent* component = tientity.getComponent<BehavesComponent>();
	if (component != nullptr) {
		if (key == BehavesComponentSystem::ROOT_FINITE_STATE_MACHINE) {
			FiniteStateMachine* rootFiniteStateMachine = component->rootFiniteStateMachine.get();
			if (rootFiniteStateMachine) {
				return ScriptManager::Instance()->getObjectFromValue(FiniteStateMachineInterface(rootFiniteStateMachine));
			}
		}
	}
	return ScriptManager::Instance()->getObjectFromValue(nullptr);
}


const std::map<std::string, std::string>& BehavesComponentSystem::getBehaviorTreeNodeTypes() {
	return this->behaviorTreeNodeTypes;
}


const std::map<std::string, std::string>& BehavesComponentSystem::getBehaviorTreeDecoratorTypes() {
	return this->behaviorTreeDecoratorTypes;
}


const std::map<std::string, int>& BehavesComponentSystem::getBehaviorTreeNodeStatuses() {
	return this->behaviorTreeNodeStatuses;
}


const BehaviorTree::NodeStatus BehavesComponentSystem::getNodeStatusForMessageSubscription(const GlobalId messageSubscription) {
	return this->messageSubscriptionToBehaviorTreeNodeStatus[messageSubscription];
}

const GlobalId BehavesComponentSystem::getMessageSubscriptionForNodeStatus(const BehaviorTree::NodeStatus nodeStatus) {
	return this->behaviorTreeNodeStatusToMessageSubscription[nodeStatus];
}


void BehavesComponentSystem::initializeBehaviorTreeNodeTypes() {
	this->behaviorTreeNodeTypes.insert({BehaviorTreeNodeFactory::LEAF_NODE, BehaviorTreeNodeFactory::LEAF_NODE});
	this->behaviorTreeNodeTypes.insert({BehaviorTreeNodeFactory::PARALLEL_NODE, BehaviorTreeNodeFactory::PARALLEL_NODE });
	this->behaviorTreeNodeTypes.insert({BehaviorTreeNodeFactory::PRIORITY_SELECTOR_NODE, BehaviorTreeNodeFactory::PRIORITY_SELECTOR_NODE });
	this->behaviorTreeNodeTypes.insert({BehaviorTreeNodeFactory::SELECTOR_NODE, BehaviorTreeNodeFactory::SELECTOR_NODE});
	this->behaviorTreeNodeTypes.insert({BehaviorTreeNodeFactory::SEQUENCE_NODE, BehaviorTreeNodeFactory::SEQUENCE_NODE });
}


void BehavesComponentSystem::initializeBehaviorTreeDecoratorTypes() {
	this->behaviorTreeDecoratorTypes.insert({BehaviorTreeNodeFactory::PRE_CONDITION, BehaviorTreeNodeFactory::PRE_CONDITION});
	this->behaviorTreeDecoratorTypes.insert({BehaviorTreeNodeFactory::POST_CONDITION, BehaviorTreeNodeFactory::POST_CONDITION});
	this->behaviorTreeDecoratorTypes.insert({BehaviorTreeNodeFactory::ON_MESSAGE, BehaviorTreeNodeFactory::ON_MESSAGE});
	this->behaviorTreeDecoratorTypes.insert({BehaviorTreeNodeFactory::WAIT_FOR_MESSAGE, BehaviorTreeNodeFactory::WAIT_FOR_MESSAGE});
	this->behaviorTreeDecoratorTypes.insert({BehaviorTreeNodeFactory::LOOP, BehaviorTreeNodeFactory::LOOP});

}


void BehavesComponentSystem::initializeBehaviorTreeNodeStatuses() {
	this->behaviorTreeNodeStatuses.insert({"Success", BehaviorTree::NodeStatus::SUCCESS});
	this->behaviorTreeNodeStatuses.insert({"Failure", BehaviorTree::NodeStatus::FAILURE});
	this->behaviorTreeNodeStatuses.insert({"Running", BehaviorTree::NodeStatus::RUNNING});
}


void BehavesComponentSystem::initializeBehaviorTreeNodeStatusMessageSubscriptions() {
	this->behaviorTreeNodeStatusToMessageSubscription.insert({ BehaviorTree::NodeStatus::SUCCESS, MessageManager::Instance()->getSubscriptionId(MessageSubscriptions::BEHAVIOR_TREE_NODE_SUCCESS) });
	this->behaviorTreeNodeStatusToMessageSubscription.insert({ BehaviorTree::NodeStatus::RUNNING, MessageManager::Instance()->getSubscriptionId(MessageSubscriptions::BEHAVIOR_TREE_NODE_RUNNING) });
	this->behaviorTreeNodeStatusToMessageSubscription.insert({ BehaviorTree::NodeStatus::FAILURE, MessageManager::Instance()->getSubscriptionId(MessageSubscriptions::BEHAVIOR_TREE_NODE_FAILURE) });

	this->messageSubscriptionToBehaviorTreeNodeStatus.insert({ this->behaviorTreeNodeStatusToMessageSubscription[BehaviorTree::NodeStatus::SUCCESS], BehaviorTree::NodeStatus::SUCCESS});
	this->messageSubscriptionToBehaviorTreeNodeStatus.insert({ this->behaviorTreeNodeStatusToMessageSubscription[BehaviorTree::NodeStatus::RUNNING], BehaviorTree::NodeStatus::RUNNING});
	this->messageSubscriptionToBehaviorTreeNodeStatus.insert({ this->behaviorTreeNodeStatusToMessageSubscription[BehaviorTree::NodeStatus::FAILURE], BehaviorTree::NodeStatus::FAILURE});
}
