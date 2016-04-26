#include <iostream>
#include <memory>

#include "ConsoleManager.h"

#include "../objects/ConsoleCommands.h"

using namespace TIE;

ConsoleManager::ConsoleManager()
{
	consoleCommands = std::make_shared<ConsoleCommands>();
}

ConsoleManager::~ConsoleManager()
{

}

void ConsoleManager::showConsole()
{
	consoleState = true;
}

void ConsoleManager::hideConsole()
{
	consoleState = false;
}

bool ConsoleManager::checkConsole()
{
	return consoleState;
}

void ConsoleManager::runCommand(const std::string& command)
{
	std::cout << command << std::endl;

	if (command == "test")
	{
		std::cout << "Command test successful" << std::endl;
	}
	//Run client commands
	else if (this->consoleCommands->processCommand(command) == 1)
	{
		std::cout << "Command not found." << std::endl;
	}
}

void ConsoleManager::setConsoleCommands(std::shared_ptr<ConsoleCommands> consoleCommands)
{
	this->consoleCommands = consoleCommands;
}
