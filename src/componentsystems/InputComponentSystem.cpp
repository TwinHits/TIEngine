#include "componentsystems/InputComponentSystem.h"

#include "objects/components/InputComponent.h"
#include "objects/components/MovesComponent.h"
#include "objects/components/SelectableComponent.h"
#include "managers/InputManager.h"

using namespace TIE;

void InputComponentSystem::update(TIEntity& entity, const float delta) {
	InputComponent* inputComponent = entity.getComponent<InputComponent>();
	if (inputComponent != nullptr) {
		const std::string& click = inputComponent->getClick();
		if (!click.empty()) {
			const sf::Event* const clickEvent = InputManager::Instance()->getEvent(sf::Event::MouseButtonPressed);
			if (clickEvent != nullptr) {
				sf::Vector2f mousePosition = sf::Vector2f(clickEvent->mouseButton.x, clickEvent->mouseButton.y);
				if (click == "setDestination") {
					MovesComponent* movesComponent = entity.getComponent<MovesComponent>();
					SelectableComponent* selectableComponent = entity.getComponent<SelectableComponent>();
					if (movesComponent != nullptr && selectableComponent != nullptr && selectableComponent->isSelected()) {
						movesComponent->setDestination(mousePosition);
						InputManager::Instance()->removeEvent(sf::Event::MouseButtonPressed);
					}
				}
			}
		}
	}
}
