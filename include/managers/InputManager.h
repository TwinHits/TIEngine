#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <map>

#include <SFML/Graphics.hpp>

namespace TIE {

class InputManager : public Singleton<InputManager>, public Manager {
	public:
		void processInput();

		const sf::Vector2f& getMouseWindowPosition();
		const sf::Vector2f& getMouseWorldPosition();
		const sf::Event* const getEvent(const sf::Event::EventType&);

		InputManager() {};
		~InputManager() {};

	private:
		void publishInputEvent(const sf::Event&);
		
		sf::Vector2f mouseWindowPosition = sf::Vector2f(0, 0);
		sf::Vector2f mouseWorldPosition = sf::Vector2f(0, 0);

		std::map<sf::Event::EventType, sf::Event> events;
};

}
#endif
