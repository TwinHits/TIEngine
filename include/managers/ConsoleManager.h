#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "templates/Singleton.h"

#include "objects/drawables/DevConsole.h"

#include "objects/enumeration/Direction.h"

namespace TIE {

class ConsoleManager : public Singleton<ConsoleManager> {
	public:
		ConsoleManager();
		~ConsoleManager();

		void showConsole();
		void hideConsole();
		bool checkConsole();
		void runCommand(const std::string&);
		void scroll(Direction direction);

		void setDevConsole(std::unique_ptr<DevConsole> devConsole);

	private:
		DevConsole* devConsole;
		GlobalId devConsoleViewId;

		void operator=(const ConsoleManager&);
		ConsoleManager(const ConsoleManager&);
};

}
#endif
