#include "managers/InputManager.h" 

#include <cstdio>

#include <SFML/Graphics.hpp>

#include "managers/ConsoleManager.h"
#include "managers/LogManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"
#include "templates/MakeUnique.h"

using namespace TIE;

bool InputManager::initialize() { 
	return true;
}


const sf::Vector2f InputManager::getMouseWindowPosition() {
	return this->mouseWindowPosition;
}


const sf::Vector2f InputManager::getMouseWorldPosition() {
	return this->mouseWorldPosition;
}


const sf::Vector2f* const InputManager::getClickPosition() {
	return this->lastClickPosition;
}


void InputManager::processInput() {
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();
	sf::View& clientView = ViewManager::Instance()->getClientView();
	sf::Vector2i position = sf::Mouse::getPosition(window);
	this->mouseWindowPosition = window.mapPixelToCoords(position);
	this->mouseWorldPosition = window.mapPixelToCoords(position, clientView); 
	this->lastClickPosition = nullptr;

	sf::Event event;
	while (window.pollEvent(event)) {

		//Window Input Commands
		if (!ConsoleManager::Instance()->checkConsole()) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				LogManager::Instance()->info("Window closed.");
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					window.close();
					LogManager::Instance()->info("Window closed.");
					break;
				case sf::Keyboard::Tilde:
					ConsoleManager::Instance()->showConsole();
					break;
				default:
					break;
				}
				break;
			case sf::Event::MouseButtonPressed:
				this->lastClickPosition = &(this->mouseWorldPosition);
				break;
			default:
				break;
			}
			continue;
		}


		//Console Input Commands
		if (ConsoleManager::Instance()->checkConsole()) {
			switch (event.type) {
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					ConsoleManager::Instance()->hideConsole();
					break;
				case sf::Keyboard::Tilde:
					ConsoleManager::Instance()->hideConsole();
					break;
				case sf::Keyboard::Return:
					ConsoleManager::Instance()->runCommand();
					break;
				case sf::Keyboard::Up:
					ConsoleManager::Instance()->traverseUpHistory();
					break;
				case sf::Keyboard::Down:
					ConsoleManager::Instance()->traverseDownHistory();
					break;
				default:
					break;
				}
				break;
			case sf::Event::TextEntered:
				ConsoleManager::Instance()->addToInput(event.text.unicode);
				break;
			default:
				break;
			}
			continue;
		}
	}

	//Check for camera scrolling
	this->scroll(window);
}


void InputManager::scroll(sf::RenderWindow& window) {

	auto consoleManager = ConsoleManager::Instance();
	auto mousePosition = sf::Mouse::getPosition(window);
	GlobalId clientViewId = ViewManager::Instance()->getClientViewId();
	Direction direction;
	
	if (!consoleManager->checkConsole()) {
		if (mousePosition.y <= scrollZone)
			ViewManager::Instance()->scroll(clientViewId, TOP);
		if (mousePosition.y >= WindowManager::Instance()->getWindowSize().y - scrollZone)
			ViewManager::Instance()->scroll(clientViewId, BOTTOM);
		if (mousePosition.x <= scrollZone)
			ViewManager::Instance()->scroll(clientViewId, LEFT);
		if (mousePosition.x >= WindowManager::Instance()->getWindowSize().x - scrollZone)
			ViewManager::Instance()->scroll(clientViewId, RIGHT);
	} else if (consoleManager->checkConsole()) {
		if (mousePosition.y <= scrollZone)
			consoleManager->scroll(TOP);
		if (mousePosition.y >= WindowManager::Instance()->getWindowSize().y - scrollZone)
			consoleManager->scroll(BOTTOM);
	}
}
