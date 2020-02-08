#include "managers/WindowManager.h"
#include "managers/StringManager.h"
#include "managers/LogManager.h"

#include "templates/MakeUnique.h"

using namespace TIE;

WindowManager::WindowManager() {
	//Creating default window that can be replaced by client defined window
	this->addWindow();
}


WindowManager::~WindowManager() {
	this->removeWindow();
}


sf::RenderWindow& WindowManager::addWindow(sf::VideoMode mode, const std::string& title, int style, const sf::ContextSettings& settings) {
	this->title = title;

	if (this->window != nullptr) {
		LogManager::Instance()->logWarn("A window has already been created, resetting and creating a new window.");
		this->removeWindow();
	}

	this->window = TIE::make_unique<sf::RenderWindow>(mode, this->title, style, settings);
	LogManager::Instance()->logDebug("Created window.");

	this->windowSize.x = this->window->getSize().x;
	this->windowSize.y = this->window->getSize().y;

	return this->getWindow();
}


void WindowManager::removeWindow() {
	this->window.reset();
}


sf::RenderWindow& WindowManager::getWindow() {
	if (this->window == nullptr) {
		LogManager::Instance()->logWarn("Window does not yet exist, creating default window");
		this->addWindow();
	}
	return *this->window;
}


void WindowManager::showFPS(const std::string& fps) {
	this->getWindow().setTitle(title + " " + fps);
}


sf::Vector2i WindowManager::getWindowSize() {
	return this->windowSize;
}


const std::string& WindowManager::getTitle() {
	return this->title;
}
