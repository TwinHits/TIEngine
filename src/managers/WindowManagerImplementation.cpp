#include "WindowManager.h"
#include "LogManager.h"

WindowManager::WindowManager() {}
WindowManager::~WindowManager() 
{
	rmWindow();
}

sf::RenderWindow& WindowManager::addWindow()
{
	if (window == nullptr)
	{
		window = new sf::RenderWindow();
		window->create(sf::VideoMode(800, 600), "My window");
		LogManager::Instance()->logInfo("Opened window.");
		return getWindow();
	}
	else
	{
		return getWindow();
	}
}

void WindowManager::rmWindow()
{
	if (window != nullptr)
	{
		delete window;
	}
}

sf::RenderWindow& WindowManager::getWindow()
{
		return *window;
}
