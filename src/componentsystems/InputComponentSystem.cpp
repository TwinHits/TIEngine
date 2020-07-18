#include "componentsystems/InputComponentSystem.h"

#include <iostream>

#include "objects/components/InputComponent.h"
#include "objects/components/MovesComponent.h"
#include "managers/InputManager.h"

using namespace TIE;

void InputComponentSystem::update(TIEntity& entity, const float delta) {
	InputComponent* inputComponent = entity.getComponent<InputComponent>();
	if (inputComponent != nullptr) {
		const std::string& click = inputComponent->getClick();
		std::cout << "Input component system" << std::endl;
		if (!click.empty() && InputManager::Instance()->getClickPosition() != nullptr) {
			if (click == "setDestination") {
				MovesComponent* movesComponent = entity.getComponent<MovesComponent>();
				if (movesComponent != nullptr) {
					movesComponent->setDestination(*InputManager::Instance()->getClickPosition());
				}
			}
		}
	}
}
