#include "componentsystems/SelectableComponentSystem.h" 

#include <SFML/Graphics.hpp>

#include "objects/components/SelectableComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "managers/InputManager.h"
#include "templates/VectorHelpers.h"

using namespace TIE;

void SelectableComponentSystem::update(TIEntity& entity, const float delta) {
	SelectableComponent* selectableComponent = entity.getComponent<SelectableComponent>();
	if (selectableComponent != nullptr && selectableComponent->isSelectable()) {
		SpriteComponent* spriteComponent = entity.getComponent<SpriteComponent>();
		if (spriteComponent != nullptr) {
			const sf::Event* const clickEvent = InputManager::Instance()->getEvent(sf::Event::MouseButtonPressed);
			if (clickEvent != nullptr) {
				sf::FloatRect globalBounds = spriteComponent->getGlobalBounds();
				sf::Vector2f mousePosition = sf::Vector2f(clickEvent->mouseButton.x, clickEvent->mouseButton.y);
				if (globalBounds.contains(mousePosition)) {
					selectableComponent->setSelected(true);
					InputManager::Instance()->removeEvent(sf::Event::MouseButtonPressed);
					/*
					} else if (selectableComponent->isSelected()) {
					selectableComponent->setSelected(false);
					InputManager::Instance()->removeEvent(sf::Event::MouseButtonPressed);
					*/
				}
			}
		}
	}
}
