#include "componentsystems/EventsComponentSystem.h"

#include "componentsystems/GridComponentSystem.h"
#include "objects/components/EventsComponent.h"
#include "objects/components/MovesComponent.h"
#include "objects/components/SelectableComponent.h"
#include "objects/components/GridComponent.h"
#include "managers/EventsManager.h"

using namespace TIE;

void EventsComponentSystem::update(TIEntity& entity, const float delta) {
	EventsComponent* eventsComponent = entity.getComponent<EventsComponent>();
	if (eventsComponent != nullptr) {

		const std::string& click = eventsComponent->getClick();
		if (!click.empty()) {

			const sf::Event* const clickEvent = this->eventsManager->getEvent(sf::Event::MouseButtonPressed);
			if (clickEvent != nullptr) {

				sf::Vector2f mousePosition = sf::Vector2f(clickEvent->mouseButton.x, clickEvent->mouseButton.y);
				if (click == "setDestination") {

					MovesComponent* movesComponent = entity.getComponent<MovesComponent>();
					SelectableComponent* selectableComponent = entity.getComponent<SelectableComponent>();
					if (movesComponent != nullptr && selectableComponent != nullptr && selectableComponent->isSelected()) {

						if (gridManager->isGridConfigured()) {
							mousePosition = GridComponentSystem::normalizePositionToGrid(mousePosition, *gridManager->getGridEntity());
						}
						movesComponent->setDestination(mousePosition);
						this->eventsManager->removeEvent(sf::Event::MouseButtonPressed);
					}
				}
			}
		}
	}
}
