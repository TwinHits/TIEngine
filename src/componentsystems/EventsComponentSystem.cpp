#include "componentsystems/EventsComponentSystem.h"

#include <string>
#include <vector>

#include "componentsystems/MovesComponentSystem.h"
#include "objects/components/EventsComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/components/MovesComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/enumeration/Direction.h"
#include "managers/EventsManager.h"
#include "utils/StringHelpers.h"

using namespace TIE;

const std::string EventsComponentSystem::EVENTS = "events";
const std::string EventsComponentSystem::SELECTED = "selected";
const std::string EventsComponentSystem::SELECTABLE = "selectable";
const std::string EventsComponentSystem::SELECTABLE_KEY = EventsComponentSystem::SELECTABLE + '.' + EventsComponentSystem::SELECTABLE;

void EventsComponentSystem::update(const float delta) {
	for (auto c : this->components) {
		if (c.eventsComponent.hasHandlers() && eventsManager->hasEvents()) {
			const std::map<sf::Event::EventType, sf::Event>& events = eventsManager->getEvents();
			for (const std::string& state : c.eventsComponent.getStates()) {
				for (auto& event : events) {
					const std::string* eventHandler = c.eventsComponent.getEventHandler(state, event.second);
					if (eventHandler != nullptr) {
						if (*eventHandler == "setDestination") {
							sf::Vector2f position = sf::Vector2f(event.second.mouseButton.x, event.second.mouseButton.y);
							MovesComponentSystem::Instance()->setTargetPosition(c.movesComponent, c.spriteComponent, position);
						} else if (*eventHandler == "up") {
							MovesComponentSystem::Instance()->setTargetPosition(c.movesComponent, c.spriteComponent, Direction::TOP);
						} else if (*eventHandler == "down") {
							MovesComponentSystem::Instance()->setTargetPosition(c.movesComponent, c.spriteComponent, Direction::BOTTOM);
						} else if (*eventHandler == "right") {
							MovesComponentSystem::Instance()->setTargetPosition(c.movesComponent, c.spriteComponent, Direction::RIGHT);
						} else if (*eventHandler == "left") {
							MovesComponentSystem::Instance()->setTargetPosition(c.movesComponent, c.spriteComponent, Direction::LEFT);
						} else if (*eventHandler == "select") {
							const sf::Event* const clickEvent = eventsManager->getEvent(sf::Event::MouseButtonPressed);
							if (clickEvent != nullptr && c.spriteComponent.getGlobalBounds().contains(sf::Vector2f(clickEvent->mouseButton.x, clickEvent->mouseButton.y))) {
								c.eventsComponent.removeState("unselected");
								c.eventsComponent.addState("selected");
							}
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
		SpriteComponent& spriteComponent = entity.addComponent<SpriteComponent>();
		MovesComponent& movesComponent = entity.addComponent<MovesComponent>();
		Components components = { eventsComponent, spriteComponent, movesComponent };

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
