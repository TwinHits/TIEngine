#include <iostream>

#include <SFML/Graphics.hpp>

#include "InputManager.h"
#include "LogManager.h"
#include "ViewManager.h"
#include "WindowManager.h"
#include "ConsoleManager.h"

#include "../objects/InputMap.h"

using namespace TIE;

InputManager::InputManager() 
{
	inputMap = std::make_shared<InputMap>();	
}

InputManager::~InputManager() {}

void InputManager::processInput()
{
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();

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
			case sf::Event::TextEntered:
				if (ConsoleManager::Instance()->checkConsole())
				{
					textInput += static_cast<char>(event.text.unicode);
				}
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						if (!ConsoleManager::Instance()->checkConsole())
						{
							window.close();
							LogManager::Instance()->logInfo("Window closed by user.");
						}
						else if (ConsoleManager::Instance()->checkConsole())
						{
							ConsoleManager::Instance()->hideConsole();
							textInput = "";
						}
						break;
					case sf::Keyboard::BackSlash:
						if (!ConsoleManager::Instance()->checkConsole())
						{
							ConsoleManager::Instance()->showConsole();
							textInput = "";
						}
						else if (ConsoleManager::Instance()->checkConsole())
						{
							ConsoleManager::Instance()->hideConsole();
							textInput = "";
						}
						break;
					case sf::Keyboard::Return:
						if (ConsoleManager::Instance()->checkConsole())
						{
							ConsoleManager::Instance()->runCommand(textInput);
							textInput = "";
						}
						break;
					default:
						break;	
				}
				break;
			default:
				break;
		}
	}

	sf::Vector2f position = window.mapPixelToCoords(sf::Mouse::getPosition(window)); 

	//Client state processing
	inputMap->processState(position);
	//Client event processing
	inputMap->processEvent(event, position);

	this->scroll(window);

}

void InputManager::scroll(sf::RenderWindow& window)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition();	
	if (mousePosition.y <= scrollZone)
		ViewManager::Instance()->scroll(TOP);
	if (mousePosition.x >= abs(window.getSize().x)-scrollZone)
		ViewManager::Instance()->scroll(RIGHT);
	if (mousePosition.y >= abs(window.getSize().y)-scrollZone)
		ViewManager::Instance()->scroll(BOTTOM);
	if (mousePosition.x <= scrollZone)
		ViewManager::Instance()->scroll(LEFT);

}

void InputManager::setInputMap(std::shared_ptr<InputMap> inputMap)
{
	this->inputMap = inputMap;
}
