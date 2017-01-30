#include <string>

#include "managers/LogManager.h"
#include "managers/AssetsManager.h"

#include "objects/DevConsole.h"

using namespace TIE;

DevConsole::DevConsole() : font(AssetsManager::Instance()->getFont("font.tff"))
{
	this->sprite.setPosition(100,100);	
	this->sprite.setTexture(AssetsManager::Instance()->getTexture("devconsole.png"));
	this->setDraw(false);
}

DevConsole::~DevConsole() {}

int DevConsole::runClientCommand(const std::string& command)
{
	LogManager::Instance()->logWarn("No client DevConsole defined.");
	return 1;
}

void DevConsole::processCommand(const std::string& command)
{
	addCommandHistory(command);

	if (command == "test")
	{
		addCommandHistory("Command test successful");
	}
	//Run client commands
	else if (this->runClientCommand(command) == 1)
	{
		addCommandHistory("Command not found.");
	}
}	

void DevConsole::addCommandHistory(const std::string& command)
{
	SceneText text;
	text.getText().setString(command);
	text.getText().setFont(font);
	text.getText().setCharacterSize(fontSize);
	text.getText().setPosition(0,writePosition);

	writePosition += 10;
	commandHistory.push_back(text);	

}

const std::vector<SceneText>& DevConsole::getCommandHistory()
{
	return commandHistory;
}
