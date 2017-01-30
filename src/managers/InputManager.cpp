#include <iostream> 
#include <cstdio>

#include <SFML/Graphics.hpp>

#include "managers/InputManager.h" 
#include "managers/LogManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"
#include "managers/ConsoleManager.h"

#include "objects/InputMap.h"

using namespace TIE;

InputManager::InputManager() 
{
	inputMap = std::make_shared<InputMap>();	
}

InputManager::~InputManager() {}

void InputManager::processInput()
{
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();
	auto consoleManager = ConsoleManager::Instance();

	sf::Event event;
	static sf::String textInput;
	while (window.pollEvent(event))
	{
		//Engine event processing
		switch (event.type)
		{
			case sf::Event::Closed:
				window.close();
				LogManager::Instance()->logInfo("Window closed by user.");
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						if (!consoleManager->checkConsole())
						{
							window.close();
							LogManager::Instance()->logInfo("Window closed by user.");
						}
						else if (consoleManager->checkConsole())
						{
							textInput.clear();
							consoleManager->hideConsole();
						}	
						break;
					//This should be Tilde, but its not detecting on my
					//keyboard. to be fixed.
					case sf::Keyboard::BackSlash:
						textInput.clear();
						if (!consoleManager->checkConsole())
						{
							consoleManager->showConsole();
						}
						else if (consoleManager->checkConsole())
						{
							consoleManager->hideConsole();
						}
						break;
					case sf::Keyboard::Return:
						if (consoleManager->checkConsole())
						{	
							consoleManager->runCommand(std::string(textInput));
							textInput.clear();
						}
						break;
					default:
						break;	
				}
				break;
			case sf::Event::TextEntered:
				//Explicitly not allowing backslash and Return by ascii code because
				//NOTHING ESE WORKED
				if (consoleManager->checkConsole() && event.text.unicode < 128 
						&& static_cast<char>(event.text.unicode) != 92
						&& static_cast<char>(event.text.unicode) != 13)
				{
					textInput += static_cast<char>(event.text.unicode);
				}
				break;
			default:
				break;
		}
	}

	sf::Vector2f position = window.mapPixelToCoords(sf::Mouse::getPosition(window)); 
	//If the console is not active
	if (!consoleManager->checkConsole())
	{
		//Client state processing
		inputMap->processState(position);
		//Client event processing
		inputMap->processEvent(event, position);
		//Check for camera scrollin 
		this->scroll(window);
	}

}

void InputManager::scroll(sf::RenderWindow& window)
{
	auto mousePosition = sf::Mouse::getPosition(window);	
	if (mousePosition.y <= scrollZone)
		ViewManager::Instance()->scroll(TOP);
	if (mousePosition.y >= std::abs(window.getSize().y - scrollZone))
		ViewManager::Instance()->scroll(BOTTOM);
	if (mousePosition.x <= scrollZone)
		ViewManager::Instance()->scroll(LEFT);
	if (mousePosition.x >= std::abs(window.getSize().x - scrollZone))
		ViewManager::Instance()->scroll(RIGHT);

}

void InputManager::setInputMap(std::shared_ptr<InputMap> inputMap)
{
	this->inputMap = inputMap;
}
