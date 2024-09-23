#include "managers/InputManager.h" 

#include <SFML/Graphics.hpp>

#include "componentsystems/EventsComponentSystem.h"
#include "managers/MessageManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"
#include "objects/Message.h"
#include "utils/constants/SfEventStringMap.h"

using namespace TIE;

const sf::Vector2f& InputManager::getMouseWindowPosition() {
	return this->mouseWindowPosition;
}


const sf::Vector2f& InputManager::getMouseWorldPosition() {
	return this->mouseWorldPosition;
}


const sf::Event* const InputManager::getEvent(const sf::Event::EventType& eventType) {
	if (this->events.find(eventType) != events.end()) {
		return &(events.at(eventType));
	}
	return nullptr;
}


void InputManager::processInput() {
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::View& clientView = ViewManager::Instance()->getClientView();
	this->mouseWindowPosition = window.mapPixelToCoords(mousePosition);
	this->mouseWorldPosition = window.mapPixelToCoords(mousePosition, clientView); 
	this->events.clear();

	sf::Event event;
	while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::MouseButtonPressed:
                event.mouseButton.x = this->mouseWorldPosition.x;
                event.mouseButton.y = this->mouseWorldPosition.y;
                break;
            default:
                break;
        }
        this->events.insert({ event.type, event });
		this->publishInputEvent(event);
	}
}


void InputManager::publishInputEvent(const sf::Event& event) {
	std::string key;
	if (event.type == sf::Event::KeyPressed) {
		key = SfEventStringMap::KEY_TO_STRING.at(event.key.code);
	} else if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			key = "LEFTMOUSEBUTTONPRESSED";
		} else if (event.mouseButton.button == sf::Mouse::Right) {
			key = "RIGHTMOUSEBUTTONPRESSED";
		}
	} else {
		key = SfEventStringMap::EVENT_TYPE_TO_STRING.at(event.type);
	}
	MessageManager::Instance()->publish(key);
	const GlobalId subscriptionId = MessageManager::Instance()->getSubscriptionId(key);
	EventsComponentSystem::Instance()->publish(Message(subscriptionId));
}
