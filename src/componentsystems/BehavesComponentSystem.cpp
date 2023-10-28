#include "componentsystems/BehavesComponentSystem.h" 

#include <string>
#include <vector>

#include "interfaces/ai/FiniteStateMachineInterface.h"
#include "managers/WorldManager.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "objects/factories/ai/FiniteStateMachineFactory.h"
#include "objects/factories/ai/BehaviorTreeNodeFactory.h"
#include "objects/tientities/TIEntity.h"
#include "utils/ComponentSystems.h"
#include "utils/types/ComponentSystemsTypes.h"

using namespace TIE;

BehavesComponentSystem::BehavesComponentSystem() {
	this->setName(BehavesComponentSystem::BEHAVES);
	ComponentSystems::insertComponentPropertyIntoMap(BehavesComponentSystem::ROOT_BEHAVIOR_TREE_NODE, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(BehavesComponentSystem::ROOT_FINITE_STATE_MACHINE, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(BehavesComponentSystem::ROOT_PAYLOAD, this->componentPropertyMap);

	this->initializeBehaviorTreeNodeTypes();
	this->initializeBehaviorTreeNodeStatuses();
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

	const GlobalId& rootPayload = factory.getReader()->get<float>(BehavesComponentSystem::ROOT_PAYLOAD, component.rootPayload);
	this->setComponentProperty(BehavesComponentSystem::ROOT_PAYLOAD, rootPayload, tientity);

	const GlobalId& rootFiniteStateMachineId = factory.getReader()->get<float>(BehavesComponentSystem::ROOT_FINITE_STATE_MACHINE, 0);
	this->setComponentProperty(BehavesComponentSystem::ROOT_FINITE_STATE_MACHINE, rootFiniteStateMachineId, tientity);

	const GlobalId& rootBehaviorTreeNodeId = factory.getReader()->get<float>(BehavesComponentSystem::ROOT_BEHAVIOR_TREE_NODE, 0);
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


void BehavesComponentSystem::addSubscriptions(TIEntity& tientity, const std::vector<GlobalId>& subscriptions, BehaviorTreeNode& node) {
	BehavesComponent& behavesComponent = this->addComponent(tientity);
	for (auto subscription : subscriptions) {
        if (!behavesComponent.subscriptions.count(subscription)) {
            behavesComponent.subscriptions[subscription];
        }
        behavesComponent.subscriptions[subscription].push_back(&node);
	}
}


void BehavesComponentSystem::onMessage(TIEntity& tientity, const Message& message) {
	std::vector<Message> messages;
	messages.push_back(message);
	this->onMessage(tientity, messages);
}


void BehavesComponentSystem::onMessage(TIEntity& tientity, const std::vector<Message>& messages) {
	BehavesComponent* component = tientity.getComponent<BehavesComponent>();
	if (component) {
		if (component->rootFiniteStateMachine) {
			for (auto& message : messages) {
				component->rootFiniteStateMachine->onMessage(message);
			}
		}
		if (component->rootBehaviorTreeNode) {
			for (auto& message : messages) {
				if (component->subscriptions.count((message.subscription))) {
					for (auto subscription : component->subscriptions.at(message.subscription)) {
						for (auto& messsage : messages) {
							subscription->onMessage(messsage);
						}
					}
				}
			}
		}
	}
}


const std::map<std::string, std::string>& BehavesComponentSystem::getBehaviorTreeNodeTypes() {
	return this->behaviorTreeNodeTypes;
}


const std::map<std::string, int>& BehavesComponentSystem::getBehaviorTreeNodeStatuses() {
	return this->behaviorTreeNodeStatuses;
}


void BehavesComponentSystem::initializeBehaviorTreeNodeTypes() {
	this->behaviorTreeNodeTypes.insert({BehaviorTreeNodeFactory::LEAF_NODE, BehaviorTreeNodeFactory::LEAF_NODE});
	this->behaviorTreeNodeTypes.insert({BehaviorTreeNodeFactory::SELECTOR_NODE, BehaviorTreeNodeFactory::SELECTOR_NODE});
	this->behaviorTreeNodeTypes.insert({BehaviorTreeNodeFactory::SEQUENCE_NODE, BehaviorTreeNodeFactory::SEQUENCE_NODE });
	this->behaviorTreeNodeTypes.insert({BehaviorTreeNodeFactory::HAS_EVENT_NODE, BehaviorTreeNodeFactory::HAS_EVENT_NODE });
	this->behaviorTreeNodeTypes.insert({BehaviorTreeNodeFactory::WAIT_FOR_EVENT_NODE, BehaviorTreeNodeFactory::WAIT_FOR_EVENT_NODE });
}


void BehavesComponentSystem::initializeBehaviorTreeNodeStatuses() {
	this->behaviorTreeNodeStatuses.insert({"Success", BehaviorTree::NodeStatus::SUCCESS});
	this->behaviorTreeNodeStatuses.insert({"Failure", BehaviorTree::NodeStatus::FAILURE});
	this->behaviorTreeNodeStatuses.insert({"Running", BehaviorTree::NodeStatus::RUNNING});
}
