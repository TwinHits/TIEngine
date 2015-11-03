#include "WindowManager.h"
#include "HashManager.h"
#include "LogManager.h"

WindowManager::WindowManager() {}
WindowManager::~WindowManager() 
{
	for (auto i = windows.begin(); i != windows.end(); i++)
	{
		rmWindow(i->first);
	}
}

RenderWindow& WindowManager::addWindow()
{
	unsigned long id = HashManager::Instance()->getNewHash();
	
	if (windows.find(id) == windows.end())
	{
		windows[id] = new RenderWindow(id);
		windows[id]->create(sf::VideoMode(800, 600), "My window");
		LogManager::Instance()->logInfo("Added window '" + std::to_string(id) + "'.");
		return *windows[id];
	}
	else
	{
		LogManager::Instance()->logWarn("Hash collison! Window '" + std::to_string(id) + "' already exists, recursively rehashing.");
		return addWindow();
	}
	
}

void WindowManager::rmWindow(unsigned long id)
{
	if (windows.find(id) != windows.end())
	{
		delete windows[id];
		LogManager::Instance()->logInfo("Deleted window '" + std::to_string(id) + "'.");
	}
	else
	{
		LogManager::Instance()->logWarn("Window '" + std::to_string(id) + "' does not exist, doing nothing.");
	}
}

RenderWindow& WindowManager::getWindow(unsigned long id)
{
	if (windows.find(id) != windows.end())
	{
		return *windows[id];
	}
	else
	{
		LogManager::Instance()->logError("Window '" + std::to_string(id) + "' does not exist, segaulting.");
		return *windows[id];
	}
}
const std::map<unsigned long, RenderWindow*>& WindowManager::getAllWindows()
{
	return windows;
}
