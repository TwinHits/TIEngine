#include "managers/EventsManager.h" 

#include <cstdio>

#include <SFML/Graphics.hpp>

#include "managers/ConsoleManager.h"
#include "managers/LogManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"
#include "templates/MakeUnique.h"

using namespace TIE;

bool EventsManager::initialize() { 
	return true;
}


const sf::Vector2f EventsManager::getMouseWindowPosition() {
	return this->mouseWindowPosition;
}


const sf::Vector2f EventsManager::getMouseWorldPosition() {
	return this->mouseWorldPosition;
}


bool EventsManager::hasEvents() {
	return this->events.size();
}


const std::map<sf::Event::EventType, sf::Event>& EventsManager::getEvents() {
	return this->events;
}


const sf::Event* const EventsManager::getEvent(sf::Event::EventType eventType) {
	if (this->events.find(eventType) != events.end()) {
		return &(events.at(eventType));
	}
	return nullptr;
}


void EventsManager::removeEvent(sf::Event::EventType eventType) {
	this->events.erase(eventType);
}


void EventsManager::processEvents() {
	sf::Vector2i position = sf::Mouse::getPosition(window);
	sf::View& clientView = ViewManager::Instance()->getClientView();
	this->mouseWindowPosition = window.mapPixelToCoords(position);
	this->mouseWorldPosition = window.mapPixelToCoords(position, clientView); 
	this->events.clear();

	sf::Event event;
	while (this->window.pollEvent(event)) {

		//Window Input Commands
		if (!consoleManager->checkConsole()) {
			switch (event.type) {
			case sf::Event::Closed:
				this->window.close();
				LogManager::Instance()->info("Window closed.");
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					this->window.close();
					LogManager::Instance()->info("Window closed.");
					break;
				case sf::Keyboard::Tilde:
					consoleManager->showConsole();
					break;
				default:
					this->events.insert({ event.type, event });
					break;
				}
				break;
			case sf::Event::MouseButtonPressed:
				event.mouseButton.x = this->mouseWorldPosition.x;
				event.mouseButton.y = this->mouseWorldPosition.y;
				this->events.insert({ event.type, event });
				break;
			case sf::Event::MouseMoved:
			case sf::Event::MouseEntered:
			case sf::Event::MouseLeft:
			case sf::Event::LostFocus:
			case sf::Event::GainedFocus:
				break;
			default:
					this->events.insert({ event.type, event });
				break;
			}
			continue;
		}


		//Console Input Commands
		if (consoleManager->checkConsole()) {
			switch (event.type) {
			case sf::Event::Closed:
				this->window.close();
				LogManager::Instance()->info("Window closed.");
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					consoleManager->hideConsole();
					break;
				case sf::Keyboard::Tilde:
					consoleManager->hideConsole();
					break;
				case sf::Keyboard::Return:
					consoleManager->runCommand();
					break;
				case sf::Keyboard::Up:
					consoleManager->traverseUpHistory();
					break;
				case sf::Keyboard::Down:
					consoleManager->traverseDownHistory();
					break;
				default:
					break;
				}
				break;
			case sf::Event::TextEntered:
				consoleManager->addToInput(event.text.unicode);
				break;
			default:
				break;
			}
			continue;
		}
	}
}

