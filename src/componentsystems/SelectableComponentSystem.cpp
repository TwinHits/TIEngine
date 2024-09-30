#include "componentsystems/SelectableComponentSystem.h" 

#include "managers/ComponentSystemsManager.h"

using namespace TIE;

SelectableComponentSystem::SelectableComponentSystem() {
	this->setName(SelectableComponentSystem::SELECTABLE);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(SelectableComponentSystem::SELECTABLE, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(SelectableComponentSystem::SELECTED, this);
}


void SelectableComponentSystem::update(const float delta) {
}


SelectableComponent& SelectableComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
	SelectableComponent& component =  this->addComponent(tientity);
	const ScriptTableReader& reader = factory.getReader().getReader(SelectableComponentSystem::SELECTABLE);

	const bool& selectable = reader.get<bool>(SelectableComponentSystem::SELECTABLE, component.isSelectable());
	component.setSelectable(selectable);

	const bool& selected = reader.get<bool>(SelectableComponentSystem::SELECTED, component.isSelected());
	component.setSelected(selected);

	return component;
}


SelectableComponent& SelectableComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<SelectableComponent>()) {
		SelectableComponent& selectableComponent = tientity.addComponent<SelectableComponent>();
		this->components.push_back({ selectableComponent, tientity });
		return selectableComponent;
	} else {
		return *tientity.getComponent<SelectableComponent>();
	}
}


bool SelectableComponentSystem::removeComponent(TIEntity& tientity) {
	SelectableComponent* selectableComponent = tientity.getComponent<SelectableComponent>();
	if (selectableComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->selectableComponent == selectableComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<SelectableComponent>();
	} else {
		return false;
	}
}

