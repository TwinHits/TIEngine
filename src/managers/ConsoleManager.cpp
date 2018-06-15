#include <memory>
#include <queue>

#include "managers/ConsoleManager.h"
#include "managers/TIEntityManager.h"
#include "managers/WindowManager.h"
#include "managers/ViewManager.h"

#include "templates/MakeUnique.h"

using namespace TIE;

ConsoleManager::ConsoleManager() {
	sf::Vector2i size = WindowManager::Instance()->getWindowSize();
	this->devConsoleViewId = ViewManager::Instance()->addView(sf::FloatRect(0, 0, size.x, size.y));
	std::unique_ptr<DevConsole> defaultDevConsole = make_unique<DevConsole>();
	this->devConsole = &*defaultDevConsole;
	TIEntityManager::Instance()->getEngineLayer().attachChild(make_unique<DevConsole>());
}


ConsoleManager::~ConsoleManager() {

} 


void ConsoleManager::showConsole() {
	this->devConsole->setDrawn(true);
}

void ConsoleManager::hideConsole() {
	this->devConsole->setDrawn(false);
}


bool ConsoleManager::checkConsole() {
	return this->devConsole->getDrawn();
}


void ConsoleManager::runCommand(const std::string& command) {
	this->devConsole->processCommand(command);
}


void ConsoleManager::renderDevConsole(const float delta) {
}


void ConsoleManager::setDevConsole(std::unique_ptr<DevConsole> devConsole) {
	SceneNode& root = TIEntityManager::Instance()->getSceneGraphRoot();
	this->devConsole = &*devConsole;
	root.detachChild(*this->devConsole);
	root.attachChild(std::move(devConsole));
}


void ConsoleManager::scroll(Direction direction) {
	sf::View view = ViewManager::Instance()->getView(this->devConsoleViewId);		
	if (direction == Direction::TOP) {
		sf::Vector2f center = view.getCenter();
		if (center.y == 0) {
			return;		
		}
		ViewManager::Instance()->scroll(direction);
	} else if (direction == Direction::BOTTOM) {
		sf::Vector2f size = view.getSize();
		sf::Vector2f center = view.getCenter();
		const sf::Vector2i writePosition = this->devConsole->getWritePosition();
		float bottomOfView = center.y + size.y /2;
		if (writePosition.y < bottomOfView) {
			return;
		}
		ViewManager::Instance()->scroll(direction);
	}
}
