#include <iostream>
#include <string>

#include "ConsoleCommands.h"

TIE::ConsoleCommands::ConsoleCommands() {}
TIE::ConsoleCommands::~ConsoleCommands() {}

void TIE::ConsoleCommands::processCommand(const std::string& command)
{
	std::cout << command << std::endl;
}
