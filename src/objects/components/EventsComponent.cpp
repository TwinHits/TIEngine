#include "objects/components/EventsComponent.h"

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

using namespace TIE;

bool EventsComponent::hasHandlers() {
	return hasEventHandlers() && hasKeyHandlers();
}


const std::string* EventsComponent::getEventHandler(const std::string& state, const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		return this->getKeyHandler(state, event.key.code);
	} else {
		return this->getEventHandler(state, event.type);
	}
	return nullptr;
}


void EventsComponent::setEventHandler(const std::string& state, const sf::Event::EventType& event, const std::string& handler) {
	if (!this->eventHandlers.count(state)) {
		this->eventHandlers.insert({ state , std::map<sf::Event::EventType, std::string>() });
	}
	auto& stateHandlers = this->eventHandlers.at(state);
	stateHandlers.insert({ event, handler });
}


const std::string* EventsComponent::getEventHandler(const std::string& state, const sf::Event::EventType& event) {
	if (this->eventHandlers.count(state)) {
		if (this->eventHandlers.at(state).count(event)) {
			return &this->eventHandlers.at(state).at(event);
		}
	}
	return nullptr;
}


bool EventsComponent::hasEventHandlers() {
	return this->eventHandlers.size();
}


void EventsComponent::setKeyHandler(const std::string& state, const sf::Keyboard::Key& key, const std::string& handler) {
	if (!this->keyHandlers.count(state)) {
		this->keyHandlers.insert({ state , 	std::map<sf::Keyboard::Key, std::string>() });
	}
	auto& stateHandlers = this->keyHandlers.at(state);
	stateHandlers.insert({ key, handler });
}


const std::string* EventsComponent::getKeyHandler(const std::string& state, const sf::Keyboard::Key& key) {
	if (this->keyHandlers.count(state)) {
		if (this->keyHandlers.at(state).count(key)) {
			return &this->keyHandlers.at(state).at(key);
		}
	}
	return nullptr;
}


bool EventsComponent::hasKeyHandlers() {
	return this->keyHandlers.size();
}
