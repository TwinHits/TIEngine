#include "componentsystems/SelectableComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/SelectableComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/EventsManager.h"
#include "templates/VectorHelpers.h"

using namespace TIE;

const std::string SelectableComponentSystem::SELECTABLE = "selectable";
const std::string SelectableComponentSystem::SELECTABLE_KEY = SelectableComponentSystem::SELECTABLE + '.' + SelectableComponentSystem::SELECTABLE;

void SelectableComponentSystem::update(TIEntity& entity, const float delta) {
	SelectableComponent* selectableComponent = entity.getComponent<SelectableComponent>();
	if (selectableComponent != nullptr && selectableComponent->isSelectable()) {
		SpriteComponent* spriteComponent = entity.getComponent<SpriteComponent>();
		if (spriteComponent != nullptr) {
			const sf::Event* const clickEvent = eventsManager->getEvent(sf::Event::MouseButtonPressed);
			if (clickEvent != nullptr) {
				if (spriteComponent->getGlobalBounds().contains(sf::Vector2f(clickEvent->mouseButton.x, clickEvent->mouseButton.y))) {
					selectableComponent->setSelected(true);
					this->eventsManager->removeEvent(sf::Event::MouseButtonPressed);
					/*
					} else if (selectableComponent->isSelected()) {
					selectableComponent->setSelected(false);
					EventManager::Instance()->removeEvent(sf::Event::MouseButtonPressed);
					*/
				}
			}
		}
	}
}

SelectableComponent* SelectableComponentSystem::addSelectableComponent(const TIEntityFactory& factory, TIEntity& entity) {

	SelectableComponent* selectablePtr = nullptr;
	if (factory.boolValues.count(SelectableComponentSystem::SELECTABLE_KEY)) {
		bool isSelectable = factory.boolValues.at(SelectableComponentSystem::SELECTABLE_KEY);
		SelectableComponent& selectableComponent = entity.addComponent<SelectableComponent>();
		selectableComponent.setSelectable(isSelectable);
	}

	return selectablePtr;
}


bool SelectableComponentSystem::isSelected(TIEntity& tientity) {
	SelectableComponent* selectableComponent = tientity.getComponent<SelectableComponent>();
	return selectableComponent != nullptr && selectableComponent->isSelected();
}
