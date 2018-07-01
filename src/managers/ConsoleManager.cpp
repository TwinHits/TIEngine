#include <memory>
#include <queue>

#include "managers/ConsoleManager.h"
#include "managers/SceneManager.h"
#include "managers/WindowManager.h"
#include "managers/ViewManager.h"
#include "templates/MakeUnique.h"

using namespace TIE;

ConsoleManager::ConsoleManager() {
	std::unique_ptr<DevConsole> defaultDevConsole = make_unique<DevConsole>();
	this->devConsole = &dynamic_cast<DevConsole&>(SceneManager::Instance()->getEngineLayer().attachChild(std::move(defaultDevConsole)));
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


void ConsoleManager::setDevConsole(std::unique_ptr<DevConsole> devConsole) {
	this->devConsole->setRemove(true);
	SceneLayer& engineLayer = SceneManager::Instance()->getEngineLayer();
	devConsole->setType("Client Defined Dev Console.");
	this->devConsole = &dynamic_cast<DevConsole&>(engineLayer.attachChild(std::move(devConsole)));
}


void ConsoleManager::scroll(Direction direction) {
	sf::View view = ViewManager::Instance()->getView(SceneManager::Instance()->getEngineLayer().getViewId());
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
