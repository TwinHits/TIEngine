#include <map>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "InputMap.h"
#include "../managers/WindowManager.h"

TIE::InputMap::InputMap() {}
TIE::InputMap::~InputMap() {}

void TIE::InputMap::process(const sf::Event& event)
{
//	sf::RenderWindow& window = WindowManager::Instance()->getWindow();
//	sf::Vector2f worldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	std::map<unsigned int, unsigned int> keyBinds;

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

	std::cout << keyBinds[event.key.code] << std::endl;
}
