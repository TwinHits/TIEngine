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
	this->recalculateScrollZones();
	return true;
}


const sf::Vector2f EventsManager::getMouseWindowPosition() {
	return this->mouseWindowPosition;
}


const sf::Vector2f EventsManager::getMouseWorldPosition() {
	return this->mouseWorldPosition;
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
	this->mouseWindowPosition = window.mapPixelToCoords(position);
	this->mouseWorldPosition = window.mapPixelToCoords(position, this->clientView); 
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
					break;
				}
				break;
			case sf::Event::MouseButtonPressed:
				event.mouseButton.x = this->mouseWorldPosition.x;
				event.mouseButton.y = this->mouseWorldPosition.y;
				this->events.insert({ event.type, event });
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

	//Check for camera scrolling
	this->scroll();
}


void EventsManager::scroll() {
		
		if (!this->consoleManager->checkConsole()) {

			if (this->scrollUpZone.contains(this->mouseWindowPosition)) {
				this->viewManager->scroll(this->clientViewId, TOP);
			}

			if (this->scrollLeftZone.contains(this->mouseWindowPosition)) {
				this->viewManager->scroll(this->clientViewId, LEFT);
			}

			if (this->scrollDownZone.contains(this->mouseWindowPosition)) {
				this->viewManager->scroll(this->clientViewId, BOTTOM);
			}

			if (this->scrollRightZone.contains(this->mouseWindowPosition)) {
				this->viewManager->scroll(this->clientViewId, RIGHT);
			}
		} else if (consoleManager->checkConsole()) {

			if (this->scrollUpZone.contains(this->mouseWindowPosition)) {
				this->consoleManager->scroll(TOP);
			}

			if (this->scrollDownZone.contains(this->mouseWindowPosition)) {
				this->consoleManager->scroll(BOTTOM);
			}
		}
}


void EventsManager::recalculateScrollZones() {
	const sf::Vector2u& windowSize = this->window.getSize();
	this->scrollUpZone = sf::FloatRect(-(int)windowSize.x / 2, -(int)windowSize.y / 2, windowSize.x, this->scrollZone);
	this->scrollDownZone = sf::FloatRect(-(int)windowSize.x / 2, (int)windowSize.y / 2 - this->scrollZone, windowSize.x, this->scrollZone);
	this->scrollLeftZone = sf::FloatRect(-(int)windowSize.x / 2, -(int)windowSize.y / 2, this->scrollZone, windowSize.y);
	this->scrollRightZone = sf::FloatRect((int)windowSize.x / 2 - this->scrollZone, -(int)windowSize.y / 2, this->scrollZone, windowSize.y);
}
