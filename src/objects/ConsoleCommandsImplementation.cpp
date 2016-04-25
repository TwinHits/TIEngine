#include <iostream>
#include <string>

#include "ConsoleCommands.h"

TIE::ConsoleCommands::ConsoleCommands() {}
TIE::ConsoleCommands::~ConsoleCommands() {}

int TIE::ConsoleCommands::processCommand(const std::string& command)
{
	std::cout << command << std::endl;
	return 0;
}
