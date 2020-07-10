#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <memory>

#include <SFML/Graphics.hpp>

#include "objects/entities/DevConsole.h"
#include "objects/enumeration/Direction.h"

namespace TIE {

class ConsoleManager : public Singleton<ConsoleManager>, Manager {
	public:
		bool initialize();

		void showConsole();
		void hideConsole();
		bool checkConsole();
		void runCommand();
		void scroll(Direction direction);
		void traverseDownHistory();
		void traverseUpHistory();
		void addToInput(unsigned int unicodeCharacter);
		const std::string& getInput();

		void setDevConsole(std::unique_ptr<DevConsole> devConsole);

		ConsoleManager() {};
		~ConsoleManager() {};
	private:
		std::vector<std::string>& splitString(const std::string& string, char delimiter, std::vector<std::string>& out);

		void printSceneGraph(TIEntity&);
		void clearConsoleHistory();
		void clearDebugLog();

		DevConsole* devConsole;
		std::string input;
		std::vector<std::string> commandHistory;
		std::vector<std::string>::iterator historyIndex = commandHistory.begin();


		void operator=(const ConsoleManager&) {};
		ConsoleManager(const ConsoleManager&);
};

}
#endif
