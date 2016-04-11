#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <map>

#include "../templates/Singleton.h"

#include "../objects/InputMap.h"

namespace TIE
{

	class InputManager : public Singleton<InputManager>
	{
		public:
			void processInput();
			void setInputMap(InputMap* inputMap);

			InputManager();
			~InputManager();
		private:
			short scrollZone = 5;
			InputMap* inputMap;	

			InputManager(const InputManager&);
			void operator=(const InputManager&);
	};

}
#endif
