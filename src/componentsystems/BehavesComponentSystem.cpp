#include "componentsystems/BehavesComponentSystem.h" 

#include "interfaces/ai/FiniteStateMachineInterface.h"
#include "managers/WorldManager.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/factories/ai/FiniteStateMachineFactory.h"
#include "objects/tientities/TIEntity.h"
#include "utils/ComponentSystems.h"
#include "utils/types/ComponentSystemsTypes.h"

using namespace TIE;

BehavesComponentSystem::BehavesComponentSystem() {
	ComponentSystems::insertComponentPropertyIntoMap(BehavesComponentSystem::ROOT_STATE, this->componentPropertyMap);
}


void BehavesComponentSystem::update(const float delta) {
	for (auto& c : components) {
		if (c.behavesComponent.rootState) {
			c.behavesComponent.rootState->update(delta);
		}
	}
}


bool BehavesComponentSystem::hasComponent(const TIEntity& tientity) {
	return tientity.hasComponent<BehavesComponent>();
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

	float rootStateId = ComponentSystems::getFactoryValue<float>(factory, BehavesComponentSystem::ROOT_STATE, 0, tientity);
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


const std::string& BehavesComponentSystem::getName() {
	return BehavesComponentSystem::BEHAVES;
}


bool BehavesComponentSystem::setComponentProperty(const std::string& key, bool value, TIEntity& tientity) {
    BehavesComponent* component = tientity.getComponent<BehavesComponent>();
	if (component != nullptr) {
	}
    return false;
}


bool BehavesComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity)  {
    BehavesComponent& component = this->addComponent(tientity);
    if (key == BehavesComponentSystem::ROOT_STATE) {
        FiniteStateMachineFactory* factory = WorldManager::Instance()->getFiniteStateMachineFactory(value);
        if (factory) {
			if (component.rootState) {
				component.rootState->onExit();
			}
            component.rootState = std::move(factory->build(tientity));
			component.rootState->onEnter();
        }
    }
	return true;
}


bool BehavesComponentSystem::setComponentProperty(const std::string& key, const sf::Vector2f& value, TIEntity& tientity)  {
	BehavesComponent* component = tientity.getComponent<BehavesComponent>();
	if (component != nullptr) {
	}
	return false;
}


bool BehavesComponentSystem::setComponentProperty(const std::string& key, const sf::Vector2i& value, TIEntity& tientity) {
	BehavesComponent* component = tientity.getComponent<BehavesComponent>();
	if (component != nullptr) {
	}
	return false;
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

