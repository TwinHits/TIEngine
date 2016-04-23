#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "../templates/Singleton.h"

#include "../objects/ConsoleCommands.h"

namespace TIE
{
	class ConsoleManager : public Singleton<ConsoleManager>
	{
		public:
			void showConsole();
			void hideConsole();
			bool checkConsole();

			void runCommand(const sf::String&);

			void setConsoleCommands(std::shared_ptr<ConsoleCommands> consoleCommands);
	
			ConsoleManager();
			~ConsoleManager();
		private:
			std::shared_ptr<ConsoleCommands> consoleCommands;

			bool consoleState = false;
	
			void operator=(const ConsoleManager&);
			ConsoleManager(const ConsoleManager&);
	};
}

#endif
