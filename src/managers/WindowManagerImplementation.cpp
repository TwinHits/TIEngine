#include "WindowManager.h"

WindowManager::WindowManager() {}
WindowManager::~WindowManager() 
{
	for (auto i = playerWindows.begin(); i != playerWindows.end(); i++)
	{
		rmWindow(i->first);
	}
}

sf::RenderWindow& WindowManager::getWindow(int id)
{
	return *playerWindows[id];
}

void WindowManager::addWindow(int id)
{
	playerWindows[id] = new sf::RenderWindow(sf::VideoMode(800, 600), "My window");
}

void WindowManager::rmWindow(int id)
{
	delete playerWindows[id];
}
