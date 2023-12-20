#include "componentsystems/EventsComponentSystem.h"

#include <string>
#include <vector>

#include "objects/GlobalId.h"
#include "objects/components/EventsComponent.h"
#include "objects/components/structs/EventState.h"
#include "objects/tientities/TIEntity.h"
#include "objects/tientities/common/SceneLayer.h"
#include "managers/ComponentSystemsManager.h"
#include "managers/EventsManager.h"
#include "managers/ScriptManager.h"
#include "managers/WindowManager.h"
#include "managers/ViewManager.h"
#include "templates/VectorHelpers.h"
#include "utils/ComponentSystems.h"
#include "utils/StringHelpers.h"

using namespace TIE;

EventsComponentSystem::EventsComponentSystem() {
	this->setName(EventsComponentSystem::EVENTS);
	this->addPropertyToComponentPropertyMap(EventsComponentSystem::SELECTED);
	this->addPropertyToComponentPropertyMap(EventsComponentSystem::UNSELECTED);
	this->addPropertyToComponentPropertyMap(EventsComponentSystem::NEUTRAL);
	this->addPropertyToComponentPropertyMap(EventsComponentSystem::HOVER);

	for (auto& [key, property] : this->componentPropertyMap) {
		ComponentSystemsManager::Instance()->registerComponentPropertyKey(key, this);
	}
}


void EventsComponentSystem::update(const float delta) {
	const sf::Event* clickEvent = EventsManager::Instance()->getEvent(sf::Event::MouseButtonPressed);
	const sf::Vector2f& worldMousePosition = EventsManager::Instance()->getMouseWorldPosition();
	const sf::Vector2f& windowMousePosition = EventsManager::Instance()->getMouseWindowPosition();

	for (auto& c : this->components) {
		// Update engine managed states
		if (clickEvent != nullptr) {
			this->updateSelectedStates(c.eventsComponent, c.tientity, *clickEvent);

		}

        if (this->isEntityInAScrollableView(c.tientity)) {
            this->updateHoverStates(c.eventsComponent, c.tientity, worldMousePosition);
        } else {
            this->updateHoverStates(c.eventsComponent, c.tientity, windowMousePosition);
        }

		// Add time elapsed to each state
		for (auto& state : c.eventsComponent.getStates()) {
			state.timeElapsed += delta;
		}

		// Check if any handlers run from events
		if (c.eventsComponent.hasHandlers() && EventsManager::Instance()->hasEvents()) {
			const std::map<sf::Event::EventType, sf::Event>& events = EventsManager::Instance()->getEvents();
			for (const EventState& state : c.eventsComponent.getStates()) {
				for (auto& event : events) {
					const GlobalId eventHandler = c.eventsComponent.getEventHandler(state.name, event.second);
					if (eventHandler) {
						ScriptManager::Instance()->runFunction<bool>(eventHandler, c.tientity);
					}
				}
			}
		}
	}
}


EventsComponent& EventsComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<EventsComponent>()) {
        EventsComponent& eventsComponent = tientity.addComponent<EventsComponent>();
        this->components.push_back({ eventsComponent, tientity });
        return eventsComponent;
	} else {
		return *tientity.getComponent<EventsComponent>();
	}
}


EventsComponent& EventsComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& entity) {
	EventsComponent& eventsComponent = this->addComponent(entity);
	const ScriptTableReader& reader = factory.getReader().getReader(EventsComponentSystem::EVENTS);

	for (auto& [state, eventReader] : reader.getReaders()) {
		for (auto& [event, functionId] : eventReader.getValues<GlobalId>()) {

			// If it's an event value store it in the events map
			sf::Event::EventType sfEvent = String::stringToEvent(event);
			if (sfEvent != sf::Event::Count) {
				eventsComponent.setEventHandler(state, sfEvent, functionId);
			}

			// If it's a keypress value store it in the keypress map
			sf::Keyboard::Key sfKey = String::stringToKey(event);
			if (sfKey != sf::Keyboard::Unknown) {
				eventsComponent.setKeyHandler(state, sfKey, functionId);
			}

			// If it's for the selected state than this component is selectable
			if (state == EventsComponentSystem::SELECTED) {
				eventsComponent.setSelectable(true);
				eventsComponent.addState(EventsComponentSystem::UNSELECTED);
			}

			// If it's for the hover state than this component is hoverable
			if (state == EventsComponentSystem::HOVER) {
				eventsComponent.setHoverable(true);
			}

		}
        // All components have neutral
        eventsComponent.addState(EventsComponentSystem::NEUTRAL);
	}

	return eventsComponent;
}



bool EventsComponentSystem::removeComponent(TIEntity& tientity) {
	EventsComponent* eventsComponent = tientity.getComponent<EventsComponent>();
	if (eventsComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->eventsComponent == eventsComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<EventsComponent>();
	} else {
		return false;
	}
}


void EventsComponentSystem::addState(TIEntity& tientity, const std::string& state) {
	EventsComponent* eventsComponent = tientity.getComponent<EventsComponent>();
	if (eventsComponent == nullptr) {
		eventsComponent = &(this->addComponent(tientity));
	}
	eventsComponent->addState(state);
}


bool EventsComponentSystem::removeState(TIEntity& tientity, const std::string& state) {
	EventsComponent* eventsComponent = tientity.getComponent<EventsComponent>();
	if (eventsComponent != nullptr) {
		eventsComponent->removeState(state);
		return true;
	} else {
		return false;
	}
}


EventState* EventsComponentSystem::getState(TIEntity& tientity, const std::string& name) {
	EventsComponent* eventsComponent = tientity.getComponent<EventsComponent>();
	if (eventsComponent != nullptr) {
		return eventsComponent->getState(name);
	} else {
		return nullptr;
	}
}


bool EventsComponentSystem::isEntityInAScrollableView(TIEntity& tientity) {
	SceneLayer* sceneLayer = nullptr;
	TIEntity* current = &tientity;
	while (current != nullptr && sceneLayer == nullptr) {
		sceneLayer = dynamic_cast<SceneLayer*>(current);
		current = &current->getParent();
	}

	return ViewManager::Instance()->isViewIdScrollable(sceneLayer->getViewId());
}


void EventsComponentSystem::updateSelectedStates(EventsComponent& eventsComponent, TIEntity& tientity, const sf::Event& clickEvent) {
    if (!eventsComponent.hasState(EventsComponentSystem::SELECTED) && eventsComponent.isSelectable()) {
        if (ComponentSystems::getGlobalBounds(tientity).contains(sf::Vector2f(clickEvent.mouseButton.x, clickEvent.mouseButton.y))) {

            eventsComponent.addState(EventsComponentSystem::SELECTED);
            eventsComponent.removeState(EventsComponentSystem::UNSELECTED);

            for (auto& eventsComponent : this->cachedSelectedComponents) {
                eventsComponent->addState(EventsComponentSystem::UNSELECTED);
                eventsComponent->removeState(EventsComponentSystem::SELECTED);
            }

			this->clearSelectedComponents();
            this->addSelectedComponent(eventsComponent);
            EventsManager::Instance()->removeEvent(sf::Event::MouseButtonPressed);
        }
    }
}


void EventsComponentSystem::updateHoverStates(EventsComponent& eventsComponent, TIEntity& tientity, const sf::Vector2f& mousePosition) {
    if (eventsComponent.isHoverable()) {
        if (ComponentSystems::getGlobalBounds(tientity).contains(mousePosition)) {
			eventsComponent.addState(EventsComponentSystem::HOVER);
		} else {
			eventsComponent.removeState(EventsComponentSystem::HOVER);
		}
    }
}


void EventsComponentSystem::addSelectedComponent(EventsComponent& eventsComponent) {
	this->cachedSelectedComponents.push_back(&eventsComponent);
}


void EventsComponentSystem::removeSelectedComponent(EventsComponent& eventsComponent) {
	Vector::remove(this->cachedSelectedComponents, &eventsComponent);
}


void EventsComponentSystem::clearSelectedComponents() {
	this->cachedSelectedComponents.clear();
}
