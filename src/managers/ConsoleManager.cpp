#include <iostream>
#include <memory>
#include <queue>

#include "managers/ConsoleManager.h"
#include "managers/LogManager.h"
#include "managers/WindowManager.h"
#include "managers/ViewManager.h"


using namespace TIE;


ConsoleManager::ConsoleManager()
{
	//make a view that happens to be the same size as the windows the client
	//created. This should not be a magic number.
	devConsoleViewId = ViewManager::Instance()->addView(sf::FloatRect(0,0,1000,1000));
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


void ConsoleManager::renderDevConsole()
{
	//Append any log messages to the scenetexts for drawing
	std::queue<std::string>& queue = LogManager::Instance()->getQueueToDraw();
	{
		while (!queue.empty())
		{
			devConsole->appendToHistory(queue.front());
			queue.pop();
		}
	}

	//Draw DevConsole last because it's always on top.
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();
	ViewManager::Instance()->setActiveView(devConsoleViewId);

	window.draw(devConsole->getSprite());
	for (auto& st : devConsole->getCommandHistory())
		window.draw(st.getText());
}


void ConsoleManager::setDevConsole(std::shared_ptr<DevConsole> devConsole)
{
	this->devConsole = devConsole;
}
