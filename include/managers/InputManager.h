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

		const sf::Vector2f* const getClickPosition();

		InputManager() {};
		~InputManager() {};

	private:
		sf::Vector2f mouseWindowPosition;
		sf::Vector2f mouseWorldPosition;
		int scrollZone = 5;
		sf::Vector2f* lastClickPosition = nullptr;

		void scroll(sf::RenderWindow&);

		InputManager(const InputManager&);
		void operator=(const InputManager&) {};
};

}
#endif
