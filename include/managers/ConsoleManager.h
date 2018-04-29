#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "templates/Singleton.h"

#include "objects/DevConsole.h"

namespace TIE {

class ConsoleManager : public Singleton<ConsoleManager> {
	public:
		ConsoleManager();
		~ConsoleManager();

		void showConsole();
		void hideConsole();
		bool checkConsole();
		void runCommand(const std::string&);
		void renderDevConsole();

		void setDevConsole(std::unique_ptr<DevConsole> devConsole);

	private:
		std::unique_ptr<DevConsole> devConsole;
		GlobalId devConsoleViewId;

		void operator=(const ConsoleManager&);
		ConsoleManager(const ConsoleManager&);
};

}
#endif
