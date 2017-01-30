#include <iostream>
#include <memory>

#include "managers/ConsoleManager.h"

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
	devConsole->setDraw(true);
}

void ConsoleManager::hideConsole()
{
	devConsole->setDraw(false);
}

bool ConsoleManager::checkConsole()
{
	return devConsole->getDraw();
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
