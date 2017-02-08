#include <string>

#include "managers/LogManager.h"
#include "managers/AssetsManager.h"

#include "objects/DevConsole.h"


using namespace TIE;


DevConsole::DevConsole() : font(AssetsManager::Instance()->getFont("font.tff"))
{
	this->sprite.setPosition(sf::Vector2f(-500,-500));
	this->sprite.setTexture(AssetsManager::Instance()->getTexture("devconsole.png"));
	this->setDraw(false);
}


DevConsole::~DevConsole() {}


const std::vector<SceneText>& DevConsole::getCommandHistory()
{
	return commandHistory;
}


int DevConsole::runClientCommand(const std::string& command)
{
	LogManager::Instance()->logWarn("No client DevConsole defined.");
	return 1;
}


void DevConsole::processCommand(const std::string& command)
{
	appendToHistory(command);

	if (command == "test")
	{
		appendToHistory("Command test successful");
	}
	//Run client commands
	else if (this->runClientCommand(command) == 1)
	{
		appendToHistory("Command not found.");
	}
}	


void DevConsole::appendToHistory(const std::string& command)
{
	SceneText text;
	text.getText().setString(command);
	text.getText().setFont(font);
	text.getText().setCharacterSize(fontSize);
	text.getText().setPosition(-500,writePosition);

	writePosition += fontSize;
	commandHistory.push_back(text);	

}

