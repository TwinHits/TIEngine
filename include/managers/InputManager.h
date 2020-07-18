#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

namespace TIE {

class InputManager : public Singleton<InputManager>, Manager {
	public:
		bool initialize();

		void processInput();
		
		const sf::Vector2f getMouseWindowPosition();
		const sf::Vector2f getMouseWorldPosition();

		const sf::Event* const getEvent(sf::Event::EventType);
		void removeEvent(sf::Event::EventType);

		InputManager() {};
		~InputManager() {};

	private:
		sf::Vector2f mouseWindowPosition;
		sf::Vector2f mouseWorldPosition;
		int scrollZone = 5;

		std::map<sf::Event::EventType, sf::Event> events;

		void scroll(sf::RenderWindow&);

		InputManager(const InputManager&);
		void operator=(const InputManager&) {};
};

}
#endif
