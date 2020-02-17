#include <iostream> 
#include <cstdio>

#include <SFML/Graphics.hpp>

#include "managers/ConfigManager.h"
#include "managers/ConsoleManager.h"
#include "managers/InputManager.h" 
#include "managers/LogManager.h"
#include "managers/SceneManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"

#include "objects/InputMap.h"

#include "templates/MakeUnique.h"

using namespace TIE;

InputManager::InputManager() { 
	inputMap = TIE::make_unique<InputMap>();	
}


InputManager::~InputManager() {

}


const std::string InputManager::getTextEntered() {
	return this->textEntered;
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
				LogManager::Instance()->logInfo("Window closed by user.");
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
					case sf::Keyboard::Escape:
						if (!consoleManager->checkConsole()) {
							window.close();
							LogManager::Instance()->logInfo("Window closed by user.");
						} else if (consoleManager->checkConsole()) {
							textEntered.clear();
							consoleManager->hideConsole();
						}	
						break;
					case sf::Keyboard::Tilde:
						textEntered.clear();
						if (!consoleManager->checkConsole()) {
							consoleManager->showConsole();
						}
						else if (consoleManager->checkConsole()) {
							consoleManager->hideConsole();
						}
						break;
					case sf::Keyboard::Return:
						if (consoleManager->checkConsole()) {	
							consoleManager->runCommand(std::string(textEntered));
							textEntered.clear();
						}
						break;
					default:
						break;	
				}
				break;
			case sf::Event::TextEntered:
				//Explicitly not allowing backslash and Return by ascii code because NOTHING ESE WORKED
				if (consoleManager->checkConsole() && event.text.unicode < 128 
						&& static_cast<char>(event.text.unicode) != 92
						&& static_cast<char>(event.text.unicode) != 13) {
					textEntered += static_cast<char>(event.text.unicode);
				}
				break;
			default:
				break;
		}

		sf::View& view = ViewManager::Instance()->getView(SceneManager::Instance()->getClientLayer().getViewId());
		sf::Vector2i position = sf::Mouse::getPosition(window);
		this->mouseWindowPosition = window.mapPixelToCoords(position);
		this->mouseWorldPosition = window.mapPixelToCoords(position, view); 

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
	GlobalId viewId = SceneManager::Instance()->getClientLayer().getViewId();
	Direction direction;
	
	if (!consoleManager->checkConsole()) {
		if (mousePosition.y <= scrollZone)
			ViewManager::Instance()->scroll(viewId, TOP);
		if (mousePosition.y >= WindowManager::Instance()->getWindowSize().y - scrollZone)
			ViewManager::Instance()->scroll(viewId, BOTTOM);
		if (mousePosition.x <= scrollZone)
			ViewManager::Instance()->scroll(viewId, LEFT);
		if (mousePosition.x >= WindowManager::Instance()->getWindowSize().x - scrollZone)
			ViewManager::Instance()->scroll(viewId, RIGHT);
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
