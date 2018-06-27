#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <memory>

#include "templates/Singleton.h"

#include "objects/InputMap.h"

namespace TIE {

class InputManager : public Singleton<InputManager> {
	public:
		void processInput();
		
		void setInputMap(std::unique_ptr<InputMap> inputMap);
		const InputMap& getInputMap();

		const std::string getTextEntered();
		const sf::Vector2f getMouseWorldPosition();

		InputManager();
		~InputManager();

	private:
		sf::String textEntered;
		int scrollZone = 5;
		std::unique_ptr<InputMap> inputMap;	

		void scroll(sf::RenderWindow& window);

		InputManager(const InputManager&);
		void operator=(const InputManager&);
};

}
#endif
