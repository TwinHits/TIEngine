#include "WindowManager.h"
#include "LogManager.h"

using namespace TIE;

WindowManager::WindowManager() {}
WindowManager::~WindowManager() 
{
	rmWindow();
}

sf::RenderWindow& WindowManager::addWindow(sf::VideoMode mode, const std::string& title, int style, const sf::ContextSettings& settings)
{
	if (window == nullptr)
	{
		this->window = new sf::RenderWindow(mode, title, style, settings);
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
	if (this->window != nullptr)
	{
		delete this->window;
	}
}

sf::RenderWindow& WindowManager::getWindow()
{
		return *window;
}
