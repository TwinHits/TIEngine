#include <string>

#include "managers/LogManager.h"
#include "managers/AssetsManager.h"
#include "managers/InputManager.h"

#include "objects/DevConsole.h"


using namespace TIE;


DevConsole::DevConsole() : font(AssetsManager::Instance()->getFont("font.tff"))
{
	this->sprite.setPosition(sf::Vector2f(-500,-500));
	//this->sprite.setTexture(AssetsManager::Instance()->getTexture("devconsole.png"));
	this->setDraw(false);
	
	//Set the currentCommand for drawing only. Maybe later combine with
	//processing?
	this->currentCommand.getText().setFont(font);
	this->currentCommand.getText().setCharacterSize(fontSize);
	this->currentCommand.getText().setPosition(-500,100);
}


DevConsole::~DevConsole()
{

}	


const std::vector<SceneText>& DevConsole::getCommandHistory()
{
	return commandHistory;
}


const SceneText& DevConsole::getCurrentCommand()
{
	return currentCommand;
}


int DevConsole::runClientCommand(const std::string& command)
{
	LogManager::Instance()->logWarn("No client DevConsole defined.");
	return 1;
}


void DevConsole::processCommand(const std::string& command)
{ LogManager::Instance()->logCommand(command);

	if (command == "test")
	{
		LogManager::Instance()->logCommand("Test Command Successful!");
	}
	//Run client commands
	else if (this->runClientCommand(command) == 1)
	{
		LogManager::Instance()->logCommand("Unknown command.");
	}
}	


void DevConsole::update()
{
	/**
	 *To get the messages to display in console, get not yet processed messages from the LogManager, turn them into scene texts, and draw them. This happens every frame.t
	 */
	auto textEntered = InputManager::Instance()->getTextEntered();
	currentCommand.getText().setString(textEntered);

	std::queue<std::string>& queue = LogManager::Instance()->getQueueToDraw();
	{
		while (!queue.empty())
		{
			auto s = queue.front();

			SceneText text;
			text.getText().setString(s);
			text.getText().setFont(font);
			text.getText().setCharacterSize(fontSize);
			text.getText().setPosition(-500,writePosition);

			writePosition += fontSize;
			commandHistory.push_back(text);	

			queue.pop();
		}
	}
}
