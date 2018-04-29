#include <memory>
#include <queue>

#include "managers/ConsoleManager.h"
#include "managers/WindowManager.h"
#include "managers/ViewManager.h"


using namespace TIE;

ConsoleManager::ConsoleManager() {
	//make a view that happens to be the same size as the windows the client created. This should not be a magic number.
	devConsoleViewId = ViewManager::Instance()->addView(sf::FloatRect(0,0,1000,1000));
	devConsole = std::make_unique<DevConsole>();
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


void ConsoleManager::renderDevConsole() {
	//Draw DevConsole last because it's always on top.
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();
	ViewManager::Instance()->setActiveView(devConsoleViewId);
	
	devConsole->update();

	window.draw(devConsole->getSprite());
	for (auto& st : devConsole->getCommandHistory())
		window.draw(st.getText());
	
	window.draw(devConsole->getCurrentCommand().getText());
}


void ConsoleManager::setDevConsole(std::unique_ptr<DevConsole> devConsole) {
	this->devConsole = std::move(devConsole);
}
