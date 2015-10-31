#include "WindowManager.h"
#include "HashManager.h"
#include "LogManager.h"

WindowManager::WindowManager() {}
WindowManager::~WindowManager() 
{
	for (auto i = playerWindows.begin(); i != playerWindows.end(); i++)
	{
		rmWindow(i->first);
	}
}

sf::RenderWindow& WindowManager::addWindow()
{
	unsigned long id = HashManager::Instance()->getNewHash();
	if (playerWindows.find(id) == playerWindows.end())
	{
		playerWindows[id] = new sf::RenderWindow(sf::VideoMode(800, 600), "My window");
		LogManager::Instance()->logInfo("Added window '" + std::to_string(id) + "'.");
		return *playerWindows[id];
	}
	else
	{
		LogManager::Instance()->logWarn("Hash collison! Window '" + std::to_string(id) + "' already exists, recursively rehashing.");
		return addWindow();
	}
}

void WindowManager::rmWindow(unsigned long id)
{
	if (playerWindows.find(id) != playerWindows.end())
	{
		delete playerWindows[id];
		LogManager::Instance()->logInfo("Deleted window '" + std::to_string(id) + "'.");
	}
	else
	{
		LogManager::Instance()->logWarn("Window '" + std::to_string(id) + "' does not exist, doing nothing.");
	}
}

sf::RenderWindow& WindowManager::getWindow(unsigned long id)
{
	if (playerWindows.find(id) != playerWindows.end())
	{
		return *playerWindows[id];
	}
	else
	{
		LogManager::Instance()->logError("Window '" + std::to_string(id) + "' does not exist, segaulting.");
		return *playerWindows[id];
	}
}
