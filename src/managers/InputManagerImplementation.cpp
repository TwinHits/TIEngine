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

InputManager::~InputManager() {}

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
						inputMap->process(event.key.code);
						break;	
				}
				break;
			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{
					case sf::Mouse::Left:
						inputMap->process(sf::Mouse::Left);
						break;
					case sf::Mouse::Right:
						inputMap->process(sf::Mouse::Right);
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
	//Check for scrolling and hover
	sf::Vector2i mouseposition = sf::Mouse::getPosition();	

	if (mouseposition.y <= scrollZone)
		ViewManager::Instance()->scroll(TOP);
	if (mouseposition.x >= abs(window.getSize().x)-scrollZone)
		ViewManager::Instance()->scroll(RIGHT);
	if (mouseposition.y >= abs(window.getSize().y)-scrollZone)
		ViewManager::Instance()->scroll(BOTTOM);
	if (mouseposition.x <= scrollZone)
		ViewManager::Instance()->scroll(LEFT);

}

void InputManager::setInputMap(InputMap* inputMap)
{
	delete this->inputMap;
	this->inputMap = inputMap;
}
