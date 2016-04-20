#include <SFML/Graphics.hpp>

#include "InputManager.h"
#include "LogManager.h"
#include "ViewManager.h"
#include "WindowManager.h"

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
	sf::Vector2f position = window.mapPixelToCoords(sf::Mouse::getPosition(window)); 

	//Client state processing
	inputMap->processState(position);

	sf::Event event;
	while (window.pollEvent(event))
	{
		position = window.mapPixelToCoords(sf::Mouse::getPosition(window)); 
		//Client event processing
		inputMap->processEvent(event, position);

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
						window.close();
						LogManager::Instance()->logInfo("Window closed by user.");
						break;
					default:
						break;	
				}
				break;
			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{
					case sf::Mouse::Left:
						break;
					case sf::Mouse::Right:
						break;
					default:
						break;
				}
				break;
			case sf::Event::MouseMoved:
				break;
			default:
				break;
		}
	}

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
