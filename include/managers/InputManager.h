#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <memory>
#include <string>

#include "objects/InputMap.h"

namespace TIE {

class InputManager : public Singleton<InputManager>, Manager {
	public:
		bool initialize();

		void processInput();
		
		void setInputMap(std::unique_ptr<InputMap> inputMap);
		const InputMap& getInputMap();

		const sf::Vector2f getMouseWindowPosition();
		const sf::Vector2f getMouseWorldPosition();

		InputManager() {};
		~InputManager() {};

	private:
		sf::Vector2f mouseWindowPosition;
		sf::Vector2f mouseWorldPosition;
		int scrollZone = 5;
		std::unique_ptr<InputMap> inputMap;	

		void scroll(sf::RenderWindow&);

		InputManager(const InputManager&);
		void operator=(const InputManager&) {};
};

}
#endif
