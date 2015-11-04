#include <iostream>

#include "EventsManager.h"
#include "WindowManager.h"
#include "LogManager.h"

EventsManager::EventsManager()
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
EventsManager::~EventsManager() {}

void EventsManager::processInput()
{
	//1) How do I condfigure a link to a function? 
	//2) How can I register a function without modifyting the eventmanager src code?
	
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
			default:
				break;
		}
	}
}
