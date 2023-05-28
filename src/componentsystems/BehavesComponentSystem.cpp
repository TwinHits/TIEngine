#include "componentsystems/BehavesComponentSystem.h" 

#include "interfaces/ai/FiniteStateMachineInterface.h"
#include "managers/WorldManager.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "objects/factories/ai/FiniteStateMachineFactory.h"
#include "objects/tientities/TIEntity.h"
#include "utils/ComponentSystems.h"
#include "utils/types/ComponentSystemsTypes.h"

using namespace TIE;

BehavesComponentSystem::BehavesComponentSystem() {
	this->setName(BehavesComponentSystem::BEHAVES);
	ComponentSystems::insertComponentPropertyIntoMap(BehavesComponentSystem::ROOT_STATE, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(BehavesComponentSystem::ROOT_PAYLOAD, this->componentPropertyMap);
}


void BehavesComponentSystem::update(const float delta) {
	for (auto& c : components) {
		if (c.behavesComponent.rootState) {
			c.behavesComponent.rootState->update(delta);
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

	const GlobalId& rootStateId = factory.getReader()->get<float>(BehavesComponentSystem::ROOT_STATE, 0);
	this->setComponentProperty(BehavesComponentSystem::ROOT_STATE, rootStateId, tientity);

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
	} else if (key == BehavesComponentSystem::ROOT_STATE) {
		FiniteStateMachineFactory* factory = WorldManager::Instance()->getFiniteStateMachineFactory(value);
		if (factory) {
			if (component.rootState) {
				component.rootState->onExit();
			}
			component.rootState = std::move(factory->build(tientity));
			component.rootState->onEnter(ScriptManager::Instance()->getObjectFromValue(component.rootPayload));
		}
    }
}


sol::object BehavesComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
	BehavesComponent* component = tientity.getComponent<BehavesComponent>();
	if (component != nullptr) {
		if (key == BehavesComponentSystem::ROOT_STATE) {
			FiniteStateMachine* root_state = component->rootState.get();
			if (root_state) {
				return ScriptManager::Instance()->getObjectFromValue(FiniteStateMachineInterface(root_state));
			}
		}
	}
	return ScriptManager::Instance()->getObjectFromValue(nullptr);
}


void BehavesComponentSystem::onMessage(TIEntity& tientity, const Message& message) {
	std::vector<Message> messages;
	messages.push_back(message);
	this->onMessage(tientity, messages);
}


void BehavesComponentSystem::onMessage(TIEntity& tientity, const std::vector<Message>& messages) {
	BehavesComponent* component = tientity.getComponent<BehavesComponent>();
	if (component && component->rootState) {
        for (auto& message : messages) {
			component->rootState->onMessage(message);
        }
	}
}
