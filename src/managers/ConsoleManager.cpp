#include <memory>
#include <queue>

#include "managers/ConsoleManager.h"
#include "managers/WindowManager.h"
#include "managers/ViewManager.h"

#include "templates/MakeUnique.h"

using namespace TIE;

ConsoleManager::ConsoleManager() {
	sf::Vector2i size = WindowManager::Instance()->getWindowSize();
	this->devConsoleViewId = ViewManager::Instance()->addView(sf::FloatRect(0, 0, size.x, size.y));
	this->devConsole = TIE::make_unique<DevConsole>();
}


ConsoleManager::~ConsoleManager() {

} 


void ConsoleManager::showConsole() {
	devConsole->setDraw(true);
}

void ConsoleManager::hideConsole() {
	devConsole->setDraw(false);
}


bool ConsoleManager::checkConsole() {
	return devConsole->getDraw();
}


void ConsoleManager::runCommand(const std::string& command) {
	this->devConsole->processCommand(command);
}


void ConsoleManager::renderDevConsole(const float delta) {
	//Draw DevConsole last because it's always on top.
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();
	ViewManager::Instance()->setActiveView(devConsoleViewId);
	
	devConsole->update(delta);

	window.draw(devConsole->getSprite());
	for (auto& st : devConsole->getCommandHistory())
		window.draw(st.getText());
	
	window.draw(devConsole->getCurrentCommand().getText());
}


void ConsoleManager::setDevConsole(std::unique_ptr<DevConsole> devConsole) {
	//devConsole.reset();
	this->devConsole = std::move(devConsole);
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
