#include "componentsystems/EventsComponentSystem.h"

#include <string>
#include <vector>

#include "componentsystems/MovesComponentSystem.h"
#include "objects/components/EventsComponent.h"
#include "objects/components/MovesComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/enumeration/Direction.h"
#include "managers/EventsManager.h"
#include "managers/ScriptManager.h"
#include "utils/StringHelpers.h"

using namespace TIE;

const std::string EventsComponentSystem::EVENTS = "events";

void EventsComponentSystem::update(const float delta) {
	this->updateSelectedStates();

	for (auto& c : this->components) {
		if (c.eventsComponent.hasHandlers() && EventsManager::Instance()->hasEvents()) {
			const std::map<sf::Event::EventType, sf::Event>& events = EventsManager::Instance()->getEvents();
			for (const std::string& state : c.eventsComponent.getStates()) {
				for (auto& event : events) {
					const std::string* eventHandler = c.eventsComponent.getEventHandler(state, event.second);
					if (eventHandler != nullptr) {
						if (*eventHandler == "setDestination") {
							sf::Vector2f position = sf::Vector2f(event.second.mouseButton.x, event.second.mouseButton.y);
							MovesComponentSystem::Instance()->setTargetPosition(c.movesComponent, c.positionComponent, position);
						} else {
							ScriptManager::Instance()->runFunction(*eventHandler, c.tientity);
						}
					}
				}
			}
		}
	}
}


void EventsComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& entity) {

	// Get all the keys containing events from the stringValues map 
	std::vector<std::string> eventKeys;
	for (auto i : factory.stringValues) {
		if (i.first.find("events.") != std::string::npos) {
			eventKeys.push_back(i.first);
		}
	}

	if (eventKeys.size()) {
		EventsComponent& eventsComponent = entity.addComponent<EventsComponent>();
		MovesComponent& movesComponent = entity.addComponent<MovesComponent>();
		PositionComponent& positionComponent = entity.addComponent<PositionComponent>();
		SpriteComponent& spriteComponent = entity.addComponent<SpriteComponent>();
		Components components = { eventsComponent, movesComponent, positionComponent, spriteComponent, entity };

		for (auto& key : eventKeys) {
			// Split the key into parts for state, event, and handler
			std::vector<std::string> keyParts = String::slice(key, '.', 1);
			std::string state = keyParts.at(0);
			std::string event = keyParts.at(1);
			std::string handler = factory.stringValues.at(key);

			// If it's an event value store it in the events map
			sf::Event::EventType sfEvent = String::stringToEvent(event);
			if (sfEvent != sf::Event::Count) {
				eventsComponent.setEventHandler(state, sfEvent, handler);
			}

			// If it's a keypress value store it in the keypress map
			sf::Keyboard::Key sfKey = String::stringToKey(event);
			if (sfKey != sf::Keyboard::Unknown) {
				eventsComponent.setKeyHandler(state, sfKey, handler);
			}
		}

		this->components.push_back(components);
	}
}


void EventsComponentSystem::updateSelectedStates() {
	const sf::Event* clickEvent = EventsManager::Instance()->getEvent(sf::Event::MouseButtonPressed);
	if (clickEvent != nullptr) {
		for (auto& c : this->components) {
			if (!c.eventsComponent.hasState("selected") && c.eventsComponent.getEventHandler("unselected", clickEvent->MouseButtonPressed) != nullptr) {
				if (c.spriteComponent.getGlobalBounds().contains(sf::Vector2f(clickEvent->mouseButton.x, clickEvent->mouseButton.y))) {
					c.eventsComponent.removeState("unselected");
					c.eventsComponent.addState("selected");
					for (auto& eventsComponent : c.eventsComponent.getSelectedComponents()) {
						eventsComponent->removeState("selected");
						eventsComponent->addState("unselected");
					}
					c.eventsComponent.clearSelectedComponents();
					c.eventsComponent.addSelectedComponent(c.eventsComponent);
					EventsManager::Instance()->removeEvent(sf::Event::MouseButtonPressed);
				}
			}
		}
	}
}

