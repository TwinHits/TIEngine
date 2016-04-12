#include <SFML/Graphics.hpp>

#include "InputManager.h"
#include "LogManager.h"
#include "ViewManager.h"
#include "WindowManager.h"

#include "../objects/InputMap.h"

using namespace TIE;

InputManager::InputManager() 
{
	inputMap = new InputMap();	
}

InputManager::~InputManager()
{
	delete inputMap;
}

void InputManager::processInput()
{
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();
	sf::Event event;
	while (window.pollEvent(event))
	{
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
						inputMap->process(event);
						break;	
				}
				break;
			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{
					case sf::Mouse::Left:
						inputMap->process(event);
						break;
					case sf::Mouse::Right:
						inputMap->process(event);
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

	//Check if we're scrolling the camera
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

void InputManager::setInputMap(InputMap* inputMap)
{
	delete this->inputMap;
	this->inputMap = inputMap;
}
