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
							textInput.clear();
							ConsoleManager::Instance()->hideConsole();
						}	
						break;
					//This should be Tilde, but its not detecting on my
					//keyboard. to be fixed.
					case sf::Keyboard::BackSlash:
						textInput.clear();
						if (!ConsoleManager::Instance()->checkConsole())
						{
							ConsoleManager::Instance()->showConsole();
						}
						else if (ConsoleManager::Instance()->checkConsole())
						{
							ConsoleManager::Instance()->hideConsole();
						}
						break;
					case sf::Keyboard::Return:
						if (ConsoleManager::Instance()->checkConsole())
						{	
							ConsoleManager::Instance()->runCommand(textInput);
							textInput.clear();
						}
						break;
					default:
						break;	
				}
				break;
			case sf::Event::TextEntered:
				//Explicitly not allowing backslash by ascii code because
				//NOTHING ESE WORKED
				if (ConsoleManager::Instance()->checkConsole() && event.text.unicode < 128 && static_cast<char>(event.text.unicode) != 92)
				{
					textInput += static_cast<char>(event.text.unicode);
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
