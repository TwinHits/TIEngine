#include "managers/HashManager.h"
#include "managers/LogManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"

using namespace TIE; 

ViewManager::ViewManager() {

}


ViewManager::~ViewManager() {

}


GlobalId ViewManager::addView() {
	return this->addView(sf::FloatRect(0,0,1000,1000));
}


GlobalId ViewManager::addView(const sf::FloatRect& rect) {
	GlobalId id = HashManager::Instance()->getNewGlobalId();
	if (this->views.find(id) == this->views.end()) {
		std::unique_ptr<sf::View> view = std::make_unique<sf::View>(rect);
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


void ViewManager::scroll(Direction direction) {
	sf::View& view = this->getActiveView();

	if (direction == TOP)
		view.move(0,-5);
	if (direction == RIGHT)
		view.move(5,0);
	if (direction == BOTTOM)
		view.move(0,5);
	if (direction == LEFT)
		view.move(-5,0);
}


void ViewManager::zoom(void) {

}