#include "WindowManager.h"
#include "StringManager.h"
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

		//Handle localization of default window title case
		if (title == "")
		{
			StringManager::Instance()->addString(title);
			window->setTitle(StringManager::Instance()->getString(title));
		}

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

void WindowManager::showFPS(const std::string& t)
{
	this->getWindow().setTitle("Twin Ion Engine " + t);
}
