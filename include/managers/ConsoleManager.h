#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "templates/Singleton.h"

#include "objects/entities/DevConsole.h"

#include "objects/enumeration/Direction.h"

namespace TIE {

class ConsoleManager : public Singleton<ConsoleManager> {
	public:
		ConsoleManager();
		~ConsoleManager() {};

		void showConsole();
		void hideConsole();
		bool checkConsole();
		void runCommand();
		void scroll(Direction direction);
		void traverseDownHistory();
		void traverseUpHistory();
		void addToCommand(unsigned int unicodeCharacter);
		const std::string& getCommand();

		void setDevConsole(std::unique_ptr<DevConsole> devConsole);

	private:
		std::vector<std::string>& splitString(const std::string& string, char delimiter, std::vector<std::string>& out);
		void printSceneGraph(TIEntity&);

		DevConsole* devConsole;
		std::string command;
		std::vector<std::string> commandHistory;
		std::vector<std::string>::iterator historyIndex;

		void operator=(const ConsoleManager&);
		ConsoleManager(const ConsoleManager&);
};

}
#endif
