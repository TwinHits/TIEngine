#include "objects/components/EventsComponent.h"

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

#include "templates/VectorHelpers.h"

using namespace TIE;

std::vector<EventsComponent*> EventsComponent::cachedSelectedComponents;

bool EventsComponent::hasHandlers() {
	return hasEventHandlers() || hasKeyHandlers();
}


const GlobalId EventsComponent::getEventHandler(const std::string& state, const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		return this->getKeyHandler(state, event.key.code);
	} else {
		return this->getEventHandler(state, event.type);
	}
}


void EventsComponent::setEventHandler(const std::string& state, const sf::Event::EventType& event, const GlobalId handler) {
	if (!this->eventHandlers.count(state)) {
		this->eventHandlers.insert({ state , std::map<sf::Event::EventType, GlobalId>() });
	}
	auto& stateHandlers = this->eventHandlers.at(state);
	stateHandlers.insert({ event, handler });
}


const GlobalId EventsComponent::getEventHandler(const std::string& state, const sf::Event::EventType& event) {
	if (this->eventHandlers.count(state)) {
		if (this->eventHandlers.at(state).count(event)) {
			return this->eventHandlers.at(state).at(event);
		}
	}
	return 0;
}


bool EventsComponent::hasEventHandlers() {
	return this->eventHandlers.size();
}


void EventsComponent::setKeyHandler(const std::string& state, const sf::Keyboard::Key& key, const GlobalId handler) {
	if (!this->keyHandlers.count(state)) {
		this->keyHandlers.insert({ state , 	std::map<sf::Keyboard::Key, GlobalId>() });
	}
	auto& stateHandlers = this->keyHandlers.at(state);
	stateHandlers.insert({ key, handler });
}


const GlobalId EventsComponent::getKeyHandler(const std::string& state, const sf::Keyboard::Key& key) {
	if (this->keyHandlers.count(state)) {
		if (this->keyHandlers.at(state).count(key)) {
			return this->keyHandlers.at(state).at(key);
		}
	}
	return 0;
}


bool EventsComponent::hasKeyHandlers() {
	return this->keyHandlers.size();
}


bool EventsComponent::hasState(const std::string& state) {
	return Vector::contains(this->states, state);
}


void EventsComponent::addState(const std::string& state) {
	if (!this->hasState(state)) {
		this->states.push_back(state);
	}
}


void EventsComponent::removeState(const std::string& state) {
	Vector::remove(this->states, state);
}


const std::vector<std::string>& TIE::EventsComponent::getStates() {
	return this->states;
}


void EventsComponent::setSelectable(bool selectable) {
	this->selectable = selectable;
}


bool EventsComponent::isSelectable() {
	return this->selectable;
}


void EventsComponent::addSelectedComponent(EventsComponent& eventsComponent) {
	this->cachedSelectedComponents.push_back(&eventsComponent);
}

std::vector<EventsComponent*>& EventsComponent::getSelectedComponents() {
	return this->cachedSelectedComponents;
}


void EventsComponent::removeSelectedComponent(EventsComponent& eventsComponent) {
	Vector::remove(this->cachedSelectedComponents, &eventsComponent);
}


void EventsComponent::clearSelectedComponents() {
	this->cachedSelectedComponents.clear();
}

