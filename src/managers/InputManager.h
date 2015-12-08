#ifndef EVENTSMANAGER_H
#define EVENTSMANAGER_H

#include <map>

#include "../templates/Singleton.h"

namespace TIE
{

	class InputManager : public Singleton<InputManager>
	{
		public:
			void processInput();

			InputManager();
			~InputManager();
		private:
			std::map<unsigned int, unsigned int> keyBinds;

			InputManager(const InputManager&);
			void operator=(const InputManager&);
	};

}
#endif
