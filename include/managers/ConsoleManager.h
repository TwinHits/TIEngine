#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <memory>

#include <SFML/Graphics.hpp>

#include "objects/enumeration/Direction.h"
#include "objects/tientities/engine/DevConsole.h"

namespace TIE {

class ConsoleManager : public Singleton<ConsoleManager>, public Manager {
	public:
		void initialize();

		bool isConsoleDrawn();
		void scroll(Direction direction);
		const std::string& getInput();

		void setDevConsole(std::unique_ptr<DevConsole> devConsole);

		ConsoleManager() {};
		~ConsoleManager() {};
	private:
		void toggleConsole();
		void runCommand();
		void traverseDownHistory();
		void traverseUpHistory();
		void appendToInput();

		void printSceneGraph(TIEntity&);
		void clearConsoleHistory();
		void clearDebugLog();
		void showGridGuide();

		DevConsole* devConsole = nullptr;
		TIEntity* currentCommand = nullptr;
		std::string input;
		std::vector<std::string> commandHistory;
		std::vector<std::string>::iterator historyIndex = commandHistory.begin();

		void operator=(const ConsoleManager&) {};
		ConsoleManager(const ConsoleManager&);
};

}
#endif
