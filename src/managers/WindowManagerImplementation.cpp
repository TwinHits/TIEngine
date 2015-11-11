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
		window = new sf::RenderWindow(sf::VideoMode(800, 600), "Twin Ion Engine 800x600");
		LogManager::Instance()->logInfo("Opened window.");
		return getWindow();
	}
	else
	{
		LogManager::Instance()->logWarn("Client attempted to open a second window. Returning existing.");
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
