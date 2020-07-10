#include "managers/ViewManager.h"

#include "managers/HashManager.h"
#include "managers/LogManager.h"
#include "managers/WindowManager.h"
#include "objects/enumeration/Direction.h"
#include "templates/MakeUnique.h"

using namespace TIE; 

bool ViewManager::initialize() {
	sf::Vector2i windowSize = WindowManager::Instance()->getWindowSize();
	this->engineViewId = this->addView(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
	this->clientViewId = this->addView(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
	return true;
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
		LogManager::Instance()->warn("Hash Collision, recursively rehashing.");		
		return this->addView();
	}
}


sf::View& ViewManager::getView(GlobalId id) {
	if (this->views.find(id) != this->views.end()) {
		return *this->views[id];
	}
	else {
		LogManager::Instance()->error("No view found by id '" + std::to_string(id) + "'. Returning nullptr.");	
		return *this->views[id];
	}
}

sf::View& ViewManager::updateView(GlobalId id, const sf::FloatRect& size) {
	sf::View& view = this->getView(id);
	return this->updateView(view, size);
}

sf::View& ViewManager::updateView(sf::View& view, const sf::FloatRect& size) {
	view.setCenter(sf::Vector2f(size.left, size.top));
	view.setSize(sf::Vector2f(size.width, size.height));
	return view;
}


sf::View& ViewManager::getActiveView() {
	if (this->activeViewId == 0) {
		LogManager::Instance()->warn("No active view found, building default.");
		this->setActiveView(this->addView());
	}

	return this->getView(this->activeViewId);
}


void ViewManager::removeView(GlobalId id) {
	auto view = this->views.find(id);
	if (view != this->views.end()) {
		this->views.erase(view);
	}
	else if (view == this->views.end()) {
		LogManager::Instance()->warn("No view found by id '" + std::to_string(id) + "'. Doing nothing.");	
	}
}


void ViewManager::setActiveView(GlobalId id) {
	sf::View& view = this->getView(id);
	WindowManager::Instance()->getWindow().setView(view);
	this->activeViewId = id;
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


void ViewManager::scroll(GlobalId viewId, Direction direction) {
	this->setActiveView(viewId);
	this->scroll(direction);
}


void ViewManager::scroll(Direction direction) {
	if (direction == TOP)
		this->getActiveView().move(0, -scrollSpeed);
	if (direction == RIGHT)
		this->getActiveView().move(scrollSpeed, 0);
	if (direction == BOTTOM)
		this->getActiveView().move(0, scrollSpeed);
	if (direction == LEFT)
		this->getActiveView().move(-scrollSpeed, 0);
}


void ViewManager::zoom(void) {

}


GlobalId ViewManager::getClientViewId() {
	return this->clientViewId;
}


GlobalId ViewManager::getEngineViewId() {
	return this->engineViewId;
}


sf::View& ViewManager::getClientView() {
	return this->getView(this->clientViewId);
}


sf::View& ViewManager::getEngineView() {
	return this->getView(this->engineViewId);
}
