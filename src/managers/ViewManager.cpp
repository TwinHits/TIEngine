#include "managers/HashManager.h"
#include "managers/LogManager.h"
#include "managers/SceneManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"

#include "objects/enumeration/Direction.h"

#include "templates/MakeUnique.h"

using namespace TIE; 

ViewManager::ViewManager() {

}


ViewManager::~ViewManager() {

}


GlobalId ViewManager::addView() {
	sf::Vector2i windowSize = WindowManager::Instance()->getWindowSize();
	return this->addView(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
}


GlobalId ViewManager::addView(const sf::FloatRect& rect) {
	GlobalId id = HashManager::Instance()->getNewGlobalId();
	if (this->views.find(id) == this->views.end()) {
		std::unique_ptr<sf::View> view = TIE::make_unique<sf::View>(rect);
		view->setCenter(0,0);
		this->views[id] = std::move(view);
		return id;
	} else {
		LogManager::Instance()->logWarn("Hash Collision, recursively rehashing.");		
		return this->addView();
	}
}


sf::View& ViewManager::getView(GlobalId id) {
	if (this->views.find(id) != this->views.end()) {
		return *this->views[id];
	}
	else {
		LogManager::Instance()->logError("No view found by id '" + std::to_string(id) + "'. Returning nullptr.");	
		return *this->views[id];
	}
}


sf::View& ViewManager::getActiveView() {
	if (this->activeView == 0) {
		LogManager::Instance()->logWarn("No active view found, building default.");
		this->setActiveView(this->addView());
	}

	return this->getView(this->activeView);
}


void ViewManager::removeView(GlobalId id) {
	auto view = this->views.find(id);
	if (view != this->views.end()) {
		this->views.erase(view);
	}
	else if (view == this->views.end()) {
		LogManager::Instance()->logWarn("No view found by id '" + std::to_string(id) + "'. Doing nothing.");	
	}
}


void ViewManager::setActiveView(GlobalId id) {
	sf::View& view = this->getView(id);
	WindowManager::Instance()->getWindow().setView(view);
	this->activeView = id;
}


void ViewManager::updateCamera() {
	WindowManager::Instance()->getWindow().setView(this->getActiveView());
}	


void ViewManager::setScrollSpeed(float scrollSpeed) {
	this->scrollSpeed = scrollSpeed;
}


float ViewManager::getScrollSpeed() {
	return this->scrollSpeed;
}


void ViewManager::scroll(Direction direction) {
	sf::View& view = this->getView(SceneManager::Instance()->getClientLayer().getViewId());

	if (direction == TOP)
		view.move(0, -scrollSpeed);
	if (direction == RIGHT)
		view.move(scrollSpeed, 0);
	if (direction == BOTTOM)
		view.move(0, scrollSpeed);
	if (direction == LEFT)
		view.move(-scrollSpeed, 0);
}


void ViewManager::zoom(void) {

}
