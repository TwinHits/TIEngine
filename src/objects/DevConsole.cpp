#include <string>

#include "managers/LogManager.h"
#include "managers/AssetsManager.h"

#include "objects/DevConsole.h"


using namespace TIE;


DevConsole::DevConsole() : font(AssetsManager::Instance()->getFont("font.tff"))
{
	this->sprite.setPosition(sf::Vector2f(-500,-500));
//	this->sprite.setTexture(AssetsManager::Instance()->getTexture("devconsole.png"));
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
	LogManager::Instance()->logCommand(command);

	if (command == "test")
	{
		LogManager::Instance()->logInfo("Test Command Successful!");
	}
	//Run client commands
	else if (this->runClientCommand(command) == 1)
	{
		LogManager::Instance()->logWarn("Unknown command.");
	}
}	


void DevConsole::update()
{
	/**
	 *To get the messages to display in console, get not yet processed messages from the LogManager, turn them into scene texts, and draw them. This happens every frame.t
	 */
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

			writePosition += fontSize + 1;
			commandHistory.push_back(text);	

			queue.pop();
		}
	}
}
