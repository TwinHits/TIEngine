#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "../templates/Singleton.h"

#include "../objects/DevConsole.h"

namespace TIE
{
	class ConsoleManager : public Singleton<ConsoleManager>
	{
		public:
			void showConsole();
			void hideConsole();
			bool checkConsole();

			void runCommand(const std::string&);

			void setDevConsole(std::shared_ptr<DevConsole> devConsole);
			const DevConsole& getDevConsole();
	
			ConsoleManager();
			~ConsoleManager();
		private:
			std::shared_ptr<DevConsole> devConsole;

			bool consoleState = false;
	
			void operator=(const ConsoleManager&);
			ConsoleManager(const ConsoleManager&);
	};
}

#endif
