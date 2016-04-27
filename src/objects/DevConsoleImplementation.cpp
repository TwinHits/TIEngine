#include <iostream>
#include <string>

#include "../managers/LogManager.h"
#include "../managers/AssetsManager.h"

#include "DevConsole.h"

using namespace TIE;

DevConsole::DevConsole() 
{
	this->sprite.setPosition(100,100);	
	this->sprite.setTexture(AssetsManager::Instance()->getTexture("devconsole.png"));
	this->setDraw(false);
}

DevConsole::~DevConsole() {}

int DevConsole::runClientCommand(const std::string& command)
{
	LogManager::Instance()->logWarn("No client DevConsole defined.");
	return 0;
}

void DevConsole::processCommand(const std::string& command)
{
	std::cout << command << std::endl;

	if (command == "test")
	{
		std::cout << "Command test successful" << std::endl;
	}
	//Run client commands
	else if (this->runClientCommand(command) == 1)
	{
		std::cout << "Command not found." << std::endl;
	}
}	
