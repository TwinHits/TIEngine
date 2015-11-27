#include "HashManager.h"
#include "LogManager.h"
#include "ViewManager.h"

using namespace TIE;

ViewManager::ViewManager() {}
ViewManager::~ViewManager()
{
	for (auto i = views.begin(); i != views.end(); ++i)
	{
		delete i->second;
	}
}

const sf::View& ViewManager::addView()
{
	GlobalId id = HashManager::Instance()->getNewGlobalId();
	if (views.find(id) == views.end())
	{
		sf::View* view = new sf::View();
		views[id] = view;
		return getView(id);
	}
	else
	{
		LogManager::Instance()->logWarn("Hash Collision, recursively rehashing.");		
		return this->addView();
	}
}

const sf::View& ViewManager::getView(GlobalId id)
{
	if (views.find(id) != views.end())
	{
		return *views[id];
	}
	else
	{
		LogManager::Instance()->logError("No view found by id '" + std::to_string(id) + "'. Returning nullptr.");	
		return *views[id];
	}
}

void ViewManager::rmView(GlobalId id)
{
	if (views.find(id) != views.end())
	{
		delete views[id];
	}
	else if (views.find(id) == views.end())
	{
		LogManager::Instance()->logWarn("No view found by id '" + std::to_string(id) + "'. Doing nothing.");	
	}
}
