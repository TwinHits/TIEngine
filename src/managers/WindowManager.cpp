#include "managers/WindowManager.h"
#include "managers/StringManager.h"
#include "managers/LogManager.h"

#include "templates/MakeUnique.h"

using namespace TIE;

WindowManager::WindowManager() {

}


WindowManager::~WindowManager() {
	this->removeWindow();
}


sf::RenderWindow& WindowManager::addWindow(sf::VideoMode mode, const std::string& title, int style, const sf::ContextSettings& settings) {
	if (!this->window) {
		//Handle localization of default window title case
		this->title = title;
		if (this->title == "Twin Ion Engine") {
			this->title = StringManager::Instance()->getString(1);
		}

		this->window = TIE::make_unique<sf::RenderWindow>(mode, this->title, style, settings);
		LogManager::Instance()->logInfo("Opened window.");

		this->windowSize.y = mode.height;
		this->windowSize.x = mode.width;

		return this->getWindow();
	} else {
		LogManager::Instance()->logWarn("Client attempted to open a second window. Returning existing.");
		return this->getWindow();
	}
}


void WindowManager::removeWindow() {
	if (this->window) {
		this->window.reset();
	}
}


sf::RenderWindow& WindowManager::getWindow() {
	if (this->window) {
		return *this->window;
	} else {
		LogManager::Instance()->logWarn("Client attempted to get a window that does not exist. Returning default new window.");
		return this->addWindow();
	}
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
