#include <iostream>

#include "InputManager.h"
#include "LogManager.h"
#include "ViewManager.h"
#include "WindowManager.h"

using namespace TIE;

InputManager::InputManager()
{
	/*
	keyBinds[sf::Keyboard::0] = 0;
	keyBinds[sf::Keyboard::1] = 1;
	keyBinds[sf::Keyboard::2] = 2;
	keyBinds[sf::Keyboard::3] = 3;
	keyBinds[sf::Keyboard::4] = 4;
	keyBinds[sf::Keyboard::5] = 5;
	keyBinds[sf::Keyboard::6] = 6;
	keyBinds[sf::Keyboard::7] = 7;
	keyBinds[sf::Keyboard::8] = 8;
	keyBinds[sf::Keyboard::9] = 9;
	*/
	keyBinds[sf::Keyboard::A] = 10;
	keyBinds[sf::Keyboard::B] = 11;
	keyBinds[sf::Keyboard::C] = 12;
	keyBinds[sf::Keyboard::D] = 13;
	keyBinds[sf::Keyboard::E] = 14;
	keyBinds[sf::Keyboard::F] = 15;
	keyBinds[sf::Keyboard::G] = 16;
	keyBinds[sf::Keyboard::H] = 17;
	keyBinds[sf::Keyboard::I] = 18;
	keyBinds[sf::Keyboard::J] = 19;
	keyBinds[sf::Keyboard::K] = 20;
	keyBinds[sf::Keyboard::L] = 21;
	keyBinds[sf::Keyboard::M] = 22;
	keyBinds[sf::Keyboard::N] = 23;
	keyBinds[sf::Keyboard::O] = 24;
	keyBinds[sf::Keyboard::P] = 25;
	keyBinds[sf::Keyboard::Q] = 26;
	keyBinds[sf::Keyboard::R] = 27;
	keyBinds[sf::Keyboard::S] = 28;
	keyBinds[sf::Keyboard::T] = 29;
	keyBinds[sf::Keyboard::U] = 30;
	keyBinds[sf::Keyboard::V] = 31;
	keyBinds[sf::Keyboard::W] = 32;
	keyBinds[sf::Keyboard::X] = 33;
	keyBinds[sf::Keyboard::Y] = 34;
	keyBinds[sf::Keyboard::Z] = 35;
	keyBinds[sf::Keyboard::Escape] = 36;

}
InputManager::~InputManager() {}

void InputManager::processInput()
{
	//1) How do I configure a link to a function? 
	//2) How can I register a function without modifying the eventmanager src code?
	
	sf::Event event;
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();
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
						std::cout << keyBinds[event.key.code] << std::endl;
						break;	
				}
				break;
			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{
					case sf::Mouse::Left:
						std::cout << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
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
	//Check for scrolling and hover
	sf::Vector2i mouseposition = sf::Mouse::getPosition();	
	short scrollZone = 5;

	if (mouseposition.y <= scrollZone)
		ViewManager::Instance()->scroll(TOP);
	if (mouseposition.x >= abs(window.getSize().x)-scrollZone)
		ViewManager::Instance()->scroll(RIGHT);
	if (mouseposition.y >= abs(window.getSize().y)-scrollZone)
		ViewManager::Instance()->scroll(BOTTOM);
	if (mouseposition.x <= scrollZone)
		ViewManager::Instance()->scroll(LEFT);
}
