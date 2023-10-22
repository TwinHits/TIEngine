#include "componentsystems/SelectableComponentSystem.h" 

#include "objects/components/SelectableComponent.h"
#include "objects/tientities/TIEntity.h"
#include "objects/factories/tientities/TIEntityFactory.h"

using namespace TIE;

SelectableComponentSystem::SelectableComponentSystem() {
	this->setName(SelectableComponentSystem::SELECTABLE);
	ComponentSystems::insertComponentPropertyIntoMap(SelectableComponentSystem::SELECTABLE_SELECTABLE, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(SelectableComponentSystem::SELECTED, this->componentPropertyMap);
}


void SelectableComponentSystem::update(const float delta) {
}


SelectableComponent& SelectableComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
	SelectableComponent& component =  this->addComponent(tientity);

	const bool& selectable = factory.getReader()->get<bool>(SelectableComponentSystem::SELECTABLE_SELECTABLE, component.isSelectable());
	const bool& selected = factory.getReader()->get<bool>(SelectableComponentSystem::SELECTED, component.isSelected());

	component.setSelectable(selectable);
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

