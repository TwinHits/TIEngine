#include "managers/WindowManager.h"

#include "managers/LogManager.h"
#include "managers/MessageManager.h"
#include "templates/MakeUnique.h"
#include "objects/constants/MessageSubscriptions.h"

using namespace TIE;

bool WindowManager::initialize() {
	//Creating default window that can be replaced by client defined window
	this->addWindow();
	return true;
}


WindowManager::~WindowManager() {
	this->removeWindow();
}


sf::RenderWindow& WindowManager::addWindow(const int style) {
	this->style = style;
	return this->addWindow();
}


sf::RenderWindow& WindowManager::addWindow(const std::string& title) {
	this->title = title;
	return this->addWindow();
}


sf::RenderWindow& WindowManager::addWindow(const sf::Vector2i& size, const std::string& title, const int style) {
	this->windowSize = size;
	this->title = title;
	this->setStyle(style);
	return this->addWindow();
}


sf::RenderWindow& WindowManager::addWindow() {
	if (this->window) {
		LogManager::Instance()->warn("A window has already been created, resetting and creating a new window.");
		this->removeWindow();
	}

	this->window = TIE::make_unique<sf::RenderWindow>(sf::VideoMode(this->getWindowSize().x, this->getWindowSize().y), this->getTitle(), this->getStyle());
	LogManager::Instance()->debug("Created window.");

	this->window->setMouseCursorGrabbed(true);
	MessageManager::Instance()->sendMessage(MessageSubscriptions::WINDOW_SIZE_CHANGE);

	return this->getWindow();
}


void WindowManager::removeWindow() {
	this->window->close();
}


sf::RenderWindow& WindowManager::getWindow() {
	if (this->window == nullptr) {
		LogManager::Instance()->warn("Window does not yet exist, creating default window");
		this->addWindow();
	}
	return *this->window;
}


sf::RenderWindow& WindowManager::updateFullScreen(const bool fullscreen) {
	this->setFullScreen(fullscreen);
	sf::RenderWindow& window = this->addWindow(this->style);
	return window;
}


sf::RenderWindow& WindowManager::updateWindowSize(const int width, const int height) {
	this->windowSize = sf::Vector2i(width, height);
	return this->addWindow();
}


const sf::Vector2i& WindowManager::getWindowSize() {
	return this->windowSize;
}


const std::string& WindowManager::getTitle() {
	return this->title;
}


void WindowManager::setTitle(const std::string& title) {
	this->title = title;
	this->getWindow().setTitle(this->title);
}


void WindowManager::setStyle(const int style) {
	this->style = style;
}


const int WindowManager::getStyle() {
	return this->style;
}


void WindowManager::setFullScreen(const bool fullscreen) {
	if (fullscreen) {
		this->style = sf::Style::Fullscreen;
	} else {
		this->style = sf::Style::Default;
	}
}


const bool WindowManager::getFullScreen() {
	return this->style == sf::Style::Fullscreen;
}
