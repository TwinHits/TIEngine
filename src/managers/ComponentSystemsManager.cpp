#include "managers/ComponentSystemsManager.h"

#include <map>
#include <vector>

#include "componentsystems/AnimatedComponentSystem.h"
#include "componentsystems/BehavesComponentSystem.h"
#include "componentsystems/ClickableComponentSystem.h"
#include "componentsystems/CollidesComponentSystem.h"
#include "componentsystems/ComponentSystem.h"
#include "componentsystems/CacheComponentSystem.h"
#include "componentsystems/EventsComponentSystem.h"
#include "componentsystems/GridComponentSystem.h"
#include "componentsystems/LifecycleComponentSystem.h"
#include "componentsystems/LineComponentSystem.h"
#include "componentsystems/MessagesComponentSystem.h"
#include "componentsystems/MovesComponentSystem.h"
#include "componentsystems/SelectableComponentSystem.h"
#include "componentsystems/ShapeComponentSystem.h"
#include "componentsystems/SpriteComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/WireframeComponentSystem.h"
#include "managers/LogManager.h"

using namespace TIE;

void ComponentSystemsManager::initialize() {
	// Component System registration, order of initialization, and order of update
	// Update data operations
	this->componentSystems.push_back(CacheComponentSystem::Instance());
	this->componentSystems.push_back(MessagesComponentSystem::Instance());
	this->componentSystems.push_back(ClickableComponentSystem::Instance());
	this->componentSystems.push_back(EventsComponentSystem::Instance());
	this->componentSystems.push_back(LifecycleComponentSystem::Instance());
	this->componentSystems.push_back(BehavesComponentSystem::Instance());
	this->componentSystems.push_back(SelectableComponentSystem::Instance());

	// Update Position Operations
	this->componentSystems.push_back(PositionComponentSystem::Instance());
	this->componentSystems.push_back(MovesComponentSystem::Instance());

	// Other Operations
	this->componentSystems.push_back(GridComponentSystem::Instance());
	this->componentSystems.push_back(CollidesComponentSystem::Instance());

	// Drawing operations
	this->componentSystems.push_back(SpriteComponentSystem::Instance());
	this->componentSystems.push_back(AnimatedComponentSystem::Instance());
	this->componentSystems.push_back(TextComponentSystem::Instance());
	this->componentSystems.push_back(ShapeComponentSystem::Instance());
	this->componentSystems.push_back(LineComponentSystem::Instance());
	this->componentSystems.push_back(WireframeComponentSystem::Instance());

	for (ComponentSystem* componentSystem : ComponentSystemsManager::Instance()->getComponentSystems()) {
		// List of valid component names
		this->componentNamesToComponentSystems[componentSystem->getName()] = componentSystem;
	}
}


const std::vector<ComponentSystem*>& ComponentSystemsManager::getComponentSystems() {
	return this->componentSystems;
}


bool ComponentSystemsManager::isValidComponentName(const std::string& componentName) {
	return this->componentNamesToComponentSystems.count(componentName);
}


ComponentSystem* ComponentSystemsManager::getComponentSystemByComponentName(const std::string& componentName) {
	if (this->isValidComponentName(componentName)) {
		return this->componentNamesToComponentSystems.at(componentName);
	} else {
		return nullptr;
	}
}


const ComponentSystems::ComponentSystemPropertiesMap& ComponentSystemsManager::getComponentSystemPropertiesMap() {
	return this->componentSystemPropertiesMap;
}


void ComponentSystemsManager::registerComponentPropertyKey(const std::string& key, ComponentSystem* componentSystem) {
	if (!this->componentSystemByPropertyKey.count(key)) {

		this->componentSystemByPropertyKey[key] = componentSystem;

		if (!this->componentSystemPropertiesMap.count(componentSystem->getName())) {
			this->componentSystemPropertiesMap[componentSystem->getName()];
		}
		this->componentSystemPropertiesMap[componentSystem->getName()][key] = key;

	} else {
		LogManager::Instance()->error("Component property " + key + " is already registered to " + this->componentSystemByPropertyKey[key]->getName()
			+ " and cannot be registered to " + componentSystem->getName());
	}
}


ComponentSystem* ComponentSystemsManager::getComponentSystemForKey(const std::string& key) {
	if (this->componentSystemByPropertyKey.count(key)) {
		return this->componentSystemByPropertyKey[key];
	} else {
		LogManager::Instance()->error("Component property " + key + " is not registered.");
		return nullptr;
	}
}


const ComponentSystems::ComponentSystemPropertyMap& ComponentSystemsManager::getComponentSystemPropertyMap(const std::string& name) {
	return this->componentSystemPropertiesMap[name];
}


void ComponentSystemsManager::updateComponentSystems(const float delta) {
    for (ComponentSystem* componentSystem : this->componentSystems) {
        componentSystem->update(delta);
    }
}


void ComponentSystemsManager::removeComponents(TIEntity& tientity) {
	LifecycleComponentSystem::Instance()->runRemoved(tientity);
	for (ComponentSystem* componentSystem : this->componentSystems) {
		componentSystem->removeComponent(tientity);
	}
}
