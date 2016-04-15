#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <memory>

#include "../templates/Singleton.h"

#include "../objects/InputMap.h"

namespace TIE
{

	class InputManager : public Singleton<InputManager>
	{
		public:
			void processInput();
			void setInputMap(std::shared_ptr<InputMap> inputMap);

			InputManager();
			~InputManager();
		private:
			short scrollZone = 5;
			std::shared_ptr<InputMap> inputMap;	

			void scroll(sf::RenderWindow& window);

			InputManager(const InputManager&);
			void operator=(const InputManager&);
	};

}
#endif
