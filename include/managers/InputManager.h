#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <memory>

#include "templates/Singleton.h"

#include "objects/InputMap.h"

namespace TIE
{

	class InputManager : public Singleton<InputManager>
	{
		public:
			void processInput();
			void setInputMap(std::shared_ptr<InputMap> inputMap);

			const std::string getTextEntered();

			InputManager();
			~InputManager();
		private:
			sf::String textEntered;
			int scrollZone = 5;
			std::shared_ptr<InputMap> inputMap;	

			void scroll(sf::RenderWindow& window);

			InputManager(const InputManager&);
			void operator=(const InputManager&);
	};

}
#endif
