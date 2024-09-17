#include "managers/ViewManager.h"

#include "constants/MessageSubscriptions.h"
#include "managers/HashManager.h"
#include "managers/LogManager.h"
#include "managers/MessageManager.h"
#include "managers/WindowManager.h"
#include "templates/MakeUnique.h"
#include "utils/TIEMath.h"

using namespace TIE;

void ViewManager::initialize() {
	const sf::Vector2i& windowSize = WindowManager::Instance()->getWindowSize();
	this->engineViewId = this->addView(sf::FloatRect(0, 0, 1.0f, 1.0f));
	this->engineView = &this->getEngineView();
	this->clientViewId = this->addView(sf::FloatRect(0, 0, 1.0f, 1.0f));
	this->clientView = &this->getClientView();
	this->recalculateScrollZones(windowSize);

	MessageManager::Instance()->subscribe(MessageSubscriptions::WINDOW_SIZE_CHANGE, std::bind(&ViewManager::onWindowSizeChange, this));
	MessageManager::Instance()->subscribe("MOUSEWHEELMOVED", std::bind(&ViewManager::onMouseWheelMoved, this));
}


GlobalId ViewManager::addView() {
	const sf::Vector2i& windowSize = WindowManager::Instance()->getWindowSize();
	return this->addView(sf::FloatRect(0, 0, 1.0f, 1.0f));
}


GlobalId ViewManager::addView(const sf::FloatRect& size) {
	return this->addView(size, sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
}


GlobalId ViewManager::addView(const sf::FloatRect& size, const sf::FloatRect& viewport) {
    GlobalId id = HashManager::Instance()->getNewGlobalId();
    std::unique_ptr<sf::View> view = TIE::make_unique<sf::View>();
    view->setCenter(0, 0);
	view->setViewport(viewport);
    this->views[id] = std::move(view);
	this->viewSizes[id] = size;

	this->updateView(*this->views[id], size);

    return id;
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


sf::View& ViewManager::updateView(sf::View& view, const sf::FloatRect& viewSize) {
	const sf::Vector2i windowSize = WindowManager::Instance()->getWindowSize();
	return this->updateView(view, viewSize, windowSize);
}


sf::View& ViewManager::updateView(sf::View& view, const sf::FloatRect& viewSize, sf::Vector2i windowSize) {
    sf::FloatRect size = sf::FloatRect(
        viewSize.left,
        viewSize.top,
        windowSize.x * viewSize.width,
        windowSize.y * viewSize.height
    );
	view.setCenter(sf::Vector2f(size.left, size.top));
	view.setSize(sf::Vector2f(size.width, size.height));
	return view;
}


void ViewManager::updateViews(const sf::Vector2i& windowSize) {
	for (auto& [id, view] : this->views) {
		const sf::FloatRect& viewSize = this->viewSizes[id];
		this->updateView(*view, viewSize, windowSize);
	}
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
	} else if (view == this->views.end()) {
		LogManager::Instance()->warn("No view found by id '" + std::to_string(id) + "'. Doing nothing.");	
	}
}


void ViewManager::setActiveView(GlobalId id) {
	sf::View& view = this->getView(id);
	this->activeViewId = id;
	MessageManager::Instance()->publish(MessageSubscriptions::ACTIVE_VIEW_CHANGE);
}


void ViewManager::updateCamera(const float delta) {
	const sf::Vector2f& mouseWindowPosition = this->inputManager->getMouseWindowPosition();
	if (!this->consoleManager->isConsoleDrawn()) {
		this->clientView->move(this->calculateClientScroll(mouseWindowPosition, delta));
	} else if (this->consoleManager->isConsoleDrawn()) {
		
	}
}	


void ViewManager::onMouseWheelMoved() {
	const sf::Event* zoomEvent = this->inputManager->getEvent(sf::Event::MouseWheelMoved);
	if (zoomEvent != nullptr) {
		float tick = 0.01666666666f;
		float change = this->zoomSpeed * tick * zoomEvent->mouseWheel.delta; //mouseWheel.delta is -1 or 1 depending on scroll direction
		if (this->currentZoom - change > this->zoomMinimum && this->currentZoom - change < this->zoomMaximum) { // But it's inverse of what I'd expect, so - to swap direction
			this->currentZoom -= change;
			const sf::Vector2i& windowSize = WindowManager::Instance()->getWindowSize();
			this->clientView->setSize(sf::Vector2f(windowSize.x * currentZoom, windowSize.y * currentZoom));
		}
	}
}


const sf::Vector2f ViewManager::calculateClientScroll(const sf::Vector2f mousePosition, const float delta) {

	sf::Vector2f translation = sf::Vector2f(0, 0);
	sf::Vector2f mouseWorldPosition = inputManager->getMouseWorldPosition();
	
	if (this->scrollBounds.contains(mouseWorldPosition)) {
		if (this->scrollUpZone.contains(mousePosition)) {
			translation += Math::translateVelocityByTime(sf::Vector2f(this->scrollSpeed, 270), delta);
		}

		if (this->scrollRightZone.contains(mousePosition)) {
			translation += Math::translateVelocityByTime(sf::Vector2f(this->scrollSpeed, 0), delta);
		}

		if (this->scrollDownZone.contains(mousePosition)) {
			translation += Math::translateVelocityByTime(sf::Vector2f(this->scrollSpeed, 90), delta);
		}

		if (this->scrollLeftZone.contains(mousePosition)) {
			translation += Math::translateVelocityByTime(sf::Vector2f(this->scrollSpeed, 180), delta);
		}
	}

	return translation;
}


void ViewManager::recalculateScrollZones(const sf::Vector2i& windowSize) {
	this->scrollUpZone = sf::FloatRect(-windowSize.x / 2, -windowSize.y / 2, windowSize.x, this->scrollZone);
	this->scrollDownZone = sf::FloatRect(-windowSize.x / 2, windowSize.y / 2 - this->scrollZone, windowSize.x, this->scrollZone);
	this->scrollLeftZone = sf::FloatRect(-windowSize.x / 2, -windowSize.y / 2, this->scrollZone, windowSize.y);
	this->scrollRightZone = sf::FloatRect(windowSize.x / 2 - this->scrollZone, -windowSize.y / 2, this->scrollZone, windowSize.y);
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


void ViewManager::setScrollBounds(const sf::FloatRect& scrollBounds) {
	this->scrollBounds = scrollBounds;
}


const sf::FloatRect& ViewManager::getScrollBounds() {
	return this->scrollBounds;
}


sf::View& ViewManager::getEngineView() {
	return this->getView(this->engineViewId);
}


bool ViewManager::isViewIdScrollable(const GlobalId id) {
	return this->clientViewId == id;
}


void ViewManager::setZoomSettings(const float speed, const float minimum, const float maximum) {
	this->zoomSpeed = speed;
	this->zoomMinimum = minimum;
	this->zoomMaximum = maximum;
}


void ViewManager::onWindowSizeChange() {
	const sf::Vector2i windowSize = WindowManager::Instance()->getWindowSize();
	this->updateViews(windowSize);
	this->recalculateScrollZones(windowSize);
}
