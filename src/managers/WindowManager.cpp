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

	this->window = TIE::make_unique<sf::RenderWindow>(mode, this->title, style, settings);
	LogManager::Instance()->logInfo("Opened window.");

	this->windowSize.y = mode.height;
	this->windowSize.x = mode.width;

	return this->getWindow();
}


void WindowManager::removeWindow() {
	this->window.reset();
}


sf::RenderWindow& WindowManager::getWindow() {
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
