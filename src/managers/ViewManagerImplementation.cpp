#include "HashManager.h"
#include "LogManager.h"
#include "ViewManager.h"
#include "WindowManager.h"

using namespace TIE; 

ViewManager::ViewManager() {}
ViewManager::~ViewManager()
{
	for (auto i = views.begin(); i != views.end(); ++i)
	{
		delete i->second;
	}
}

GlobalId ViewManager::addView()
{
	return this->addView(sf::FloatRect(0,0,1000,1000));
}

GlobalId ViewManager::addView(const sf::FloatRect& rect)
{
	GlobalId id = HashManager::Instance()->getNewGlobalId();
	if (views.find(id) == views.end())
	{
		sf::View* view = new sf::View(rect);
		view->setCenter(0,0);
		views[id] = view;
		return id;
	}
	else
	{
		LogManager::Instance()->logWarn("Hash Collision, recursively rehashing.");		
		return this->addView();
	}
}

sf::View& ViewManager::getView(GlobalId id)
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

sf::View& ViewManager::getCurrentView()
{
	return this->getView(this->activeView);
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

void ViewManager::changeCurrentView(GlobalId id)
{
	sf::View& view = this->getView(id);
	WindowManager::Instance()->getWindow().setView(view);
	this->activeView = id;
}

void ViewManager::updateCamera()
{
	WindowManager::Instance()->getWindow().setView(this->getCurrentView());
}	

void ViewManager::scroll(int direction)
{
	sf::View& view = this->getCurrentView();
	if (direction == 1)
		view.move(0,-5);
	if (direction == 2)
		view.move(5,0);
	if (direction == 3)
		view.move(0,5);
	if (direction == 4)
		view.move(-5,0);
}
