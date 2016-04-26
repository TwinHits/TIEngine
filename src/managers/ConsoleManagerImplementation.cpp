#include <iostream>
#include <memory>

#include "ConsoleManager.h"

using namespace TIE;

ConsoleManager::ConsoleManager()
{
	devConsole = std::make_shared<DevConsole>();
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
	this->devConsole->processCommand(command);
}

void ConsoleManager::setDevConsole(std::shared_ptr<DevConsole> devConsole)
{
	this->devConsole = devConsole;
}

const DevConsole& ConsoleManager::getDevConsole()
{
	return *devConsole;	
}
