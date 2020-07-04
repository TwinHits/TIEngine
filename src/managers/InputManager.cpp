#include "managers/InputManager.h" 

#include <cstdio>

#include <SFML/Graphics.hpp>

#include "managers/ConsoleManager.h"
#include "managers/LogManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"
#include "objects/InputMap.h"
#include "templates/MakeUnique.h"

using namespace TIE;

InputManager::InputManager() { 
	inputMap = TIE::make_unique<InputMap>();	
}


const sf::Vector2f InputManager::getMouseWindowPosition() {
	return this->mouseWindowPosition;
}


const sf::Vector2f InputManager::getMouseWorldPosition() {
	return this->mouseWorldPosition;
}


void InputManager::processInput() {
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();
	auto consoleManager = ConsoleManager::Instance();

	sf::Event event;
	while (window.pollEvent(event)) {
		//Engine event processing
		switch (event.type) {
			case sf::Event::Closed:
				window.close();
				LogManager::Instance()->info("Window closed by user.");
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
					case sf::Keyboard::Escape:
						if (!consoleManager->checkConsole()) {
							window.close();
							LogManager::Instance()->info("Window closed by user.");
						} else if (consoleManager->checkConsole()) {
							consoleManager->hideConsole();
						}	
						break;
					case sf::Keyboard::Tilde:
						if (!consoleManager->checkConsole()) {
							consoleManager->showConsole();
						}
						else if (consoleManager->checkConsole()) {
							consoleManager->hideConsole();
						}
						break;
					case sf::Keyboard::Return:
						if (consoleManager->checkConsole()) {	
							consoleManager->runCommand();
						}
						break;
					case sf::Keyboard::Up:
						if (consoleManager->checkConsole()) {	
							consoleManager->traverseUpHistory();
						}
						break;
					case sf::Keyboard::Down:
						if (consoleManager->checkConsole()) {	
							consoleManager->traverseDownHistory();
						}
						break;
					default:
						break;	
				}
				break;
			case sf::Event::TextEntered:
				if (consoleManager->checkConsole()) {
					consoleManager->addToCommand(event.text.unicode);
				}
				break;
			default:
				break;
		}

		sf::View& clientView = ViewManager::Instance()->getClientView();
		sf::Vector2i position = sf::Mouse::getPosition(window);
		this->mouseWindowPosition = window.mapPixelToCoords(position);
		this->mouseWorldPosition = window.mapPixelToCoords(position, clientView); 

		//Do client side event processing if the console is not showing
		if (!consoleManager->checkConsole()) {
			//Client state processing
			inputMap->processState(mouseWorldPosition);
			//Client event processing
			inputMap->processEvent(event, mouseWorldPosition);
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


void InputManager::setInputMap(std::unique_ptr<InputMap> inputMap) {
	this->inputMap = std::move(inputMap);
}


const InputMap& InputManager::getInputMap() {
	return *inputMap;
}
