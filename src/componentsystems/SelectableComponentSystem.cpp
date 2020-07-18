#include "componentsystems/SelectableComponentSystem.h" 

#include <iostream>

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
			InputManager* inputManager = InputManager::Instance();
			const sf::Vector2f* const mousePosition = inputManager->getClickPosition();
			std::cout << "Selectable Component System" << std::endl;
			if (mousePosition != nullptr) {
				sf::FloatRect globalBounds = spriteComponent->getGlobalBounds();
				if (globalBounds.contains(*mousePosition)) {
					selectableComponent->setSelected(true);
				} else if (selectableComponent->isSelected()) {
					selectableComponent->setSelected(false);
				}
			}
		}
	}
}
