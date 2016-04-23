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
	std::cout << "show" << std::endl;
	consoleState = true;
}

void ConsoleManager::hideConsole()
{
	std::cout << "hide" << std::endl;
	consoleState = false;
}

bool ConsoleManager::checkConsole()
{
	return consoleState;
}

void ConsoleManager::runCommand(const sf::String& input)
{
	std::string command = input;
	//pass to consoleCommands
	std::cout << command << std::endl;
}

void ConsoleManager::setConsoleCommands(std::shared_ptr<ConsoleCommands> consoleCommands)
{
	this->consoleCommands = consoleCommands;
}
