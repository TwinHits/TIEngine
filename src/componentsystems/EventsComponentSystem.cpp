#include "componentsystems/EventsComponentSystem.h"

#include <string>
#include <vector>

#include "componentsystems/MovesComponentSystem.h"
#include "componentsystems/SelectableComponentSystem.h"
#include "objects/components/EventsComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/enumeration/Direction.h"
#include "managers/EventsManager.h"
#include "utilities/StringHelpers.h"

using namespace TIE;

const std::string EventsComponentSystem::EVENTS = "events";
const std::string EventsComponentSystem::SELECTED = "selected";

void EventsComponentSystem::update(TIEntity& entity, const float delta) {
	EventsComponent* eventsComponent = entity.getComponent<EventsComponent>();
	if (eventsComponent != nullptr && eventsComponent->hasHandlers() && eventsManager->hasEvents()) {
		const std::map<sf::Event::EventType, sf::Event>& events = eventsManager->getEvents();
		std::vector<std::string> states;
		states = this->getStates(entity, states);
		for (const std::string& state : states) {
			for (auto event : events) {
				const std::string* eventHandler = eventsComponent->getEventHandler(state, event.second);
				if (eventHandler != nullptr) {
					if (*eventHandler == "setDestination") {
						MovesComponentSystem::setDestination(entity, sf::Vector2f(event.second.mouseButton.x, event.second.mouseButton.y));
					} else if (*eventHandler == "up") {
						MovesComponentSystem::setDestination(entity, Direction::TOP);
					} else if (*eventHandler == "down") {
						MovesComponentSystem::setDestination(entity, Direction::BOTTOM);
					} else if (*eventHandler == "right") {
						MovesComponentSystem::setDestination(entity, Direction::RIGHT);
					} else if (*eventHandler == "left") {
						MovesComponentSystem::setDestination(entity, Direction::LEFT);
					}
				}
			}
		}
	}
}


EventsComponent* TIE::EventsComponentSystem::addEventsComponent(const TIEntityFactory& factory, TIEntity& entity) {
	EventsComponent* eventsComponent = nullptr;

	// Get all the keys containing events from the stringValues map 
	std::vector<std::string> eventKeys;
	for (auto i : factory.stringValues) {
		if (i.first.find("events.") != std::string::npos) {
			eventKeys.push_back(i.first);
		}
	}

	if (eventKeys.size()) {
		eventsComponent = entity.addComponent<EventsComponent>();

		for (auto key : eventKeys) {
			// Split the key into parts for state, event, and handler
			std::vector<std::string> parts;
			String::split(key, '.', parts);
			std::string state = parts.at(1);
			std::string event = parts.at(2);
			std::string handler = factory.stringValues.at(key);

			// If it's an event value store it in the events map
			sf::Event::EventType sfEvent = String::stringToEvent(event);
			if (sfEvent != sf::Event::Count) {
				eventsComponent->setEventHandler(state, sfEvent, handler);
			}

			// If it's a keypress value store it in the keypress map
			sf::Keyboard::Key sfKey = String::stringToKey(event);
			if (sfKey != sf::Keyboard::Unknown) {
				eventsComponent->setKeyHandler(state, sfKey, handler);
			}
		}
	}

	return eventsComponent;
}


std::vector<std::string>& EventsComponentSystem::getStates(TIEntity& tientity, std::vector<std::string>& states) {
	if (SelectableComponentSystem::isSelected(tientity)) {
		states.push_back("selected");
	} else {
		states.push_back("unselected");
	}
	return states;
}
