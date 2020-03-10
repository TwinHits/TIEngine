#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <memory>
#include <string>

#include "templates/Singleton.h"

#include "objects/InputMap.h"

namespace TIE {

class InputManager : public Singleton<InputManager> {
	public:
		void processInput();
		
		void setInputMap(std::unique_ptr<InputMap> inputMap);
		const InputMap& getInputMap();

		const sf::Vector2f getMouseWindowPosition();
		const sf::Vector2f getMouseWorldPosition();

		InputManager();
		~InputManager();

	private:
		sf::Vector2f mouseWindowPosition;
		sf::Vector2f mouseWorldPosition;
		int scrollZone = 5;
		std::unique_ptr<InputMap> inputMap;	

		void scroll(sf::RenderWindow&);

		InputManager(const InputManager&);
		void operator=(const InputManager&);
};

}
#endif
