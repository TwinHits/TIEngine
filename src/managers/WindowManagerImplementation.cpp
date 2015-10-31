#include "WindowManager.h"
#include "LogManager.h"

WindowManager::WindowManager() {}
WindowManager::~WindowManager() 
{
	for (auto i = playerWindows.begin(); i != playerWindows.end(); i++)
	{
		rmWindow(i->first);
	}
}

void WindowManager::addWindow(int id)
{
	playerWindows[id] = new sf::RenderWindow(sf::VideoMode(800, 600), "My window");
	LogManager::Instance()->logInfo("Added window '" + std::to_string(id) + "'.");
}

void WindowManager::rmWindow(int id)
{
	delete playerWindows[id];
	LogManager::Instance()->logInfo("Deleted window '" + std::to_string(id) + "'.");
}

sf::RenderWindow& WindowManager::getWindow(int id)
{
	return *playerWindows[id];
}
