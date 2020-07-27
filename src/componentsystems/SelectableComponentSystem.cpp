#include "componentsystems/SelectableComponentSystem.h" 

#include <SFML/Graphics.hpp>

#include "objects/components/SelectableComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "managers/EventsManager.h"
#include "templates/VectorHelpers.h"

using namespace TIE;

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
