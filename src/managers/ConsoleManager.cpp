#include <memory>
#include <queue>
#include <sstream>

#include "managers/ConsoleManager.h"
#include "managers/LogManager.h"
#include "managers/SceneManager.h"
#include "managers/ScriptManager.h"
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


void ConsoleManager::runCommand() {
   	LogManager::Instance()->logCommand(this->command);
	this->commandHistory.push_back(this->command);

	std::vector<std::string> commandArgs;
	this->splitString(this->command, ' ', commandArgs);
	const std::string& command = commandArgs.front();

	if (command == "test") {
		LogManager::Instance()->logCommand("Test Command Please Ignore.");
	} else if (command == "script") {
		const std::string& scriptName = commandArgs.at(1);
		ScriptManager::Instance()->loadScript(scriptName);
	} else {
		LogManager::Instance()->logCommand("Unknown command.");
	}
}


const std::string& ConsoleManager::getCommand() {
	return this->command;
}


void ConsoleManager::setDevConsole(std::unique_ptr<DevConsole> devConsole) {
	this->devConsole->setRemove(true);
	SceneLayer& engineLayer = SceneManager::Instance()->getEngineLayer();
	devConsole->setType("Client Defined Dev Console.");
	this->devConsole = &dynamic_cast<DevConsole&>(engineLayer.attachChild(std::move(devConsole)));
}


void ConsoleManager::scroll(Direction direction) {
	GlobalId engineViewId = ViewManager::Instance()->getEngineViewId();
	sf::View& engineView = ViewManager::Instance()->getEngineView();
	if (direction == Direction::TOP) {
		sf::Vector2f center = engineView.getCenter();
		if (center.y == 0) {
			return;		
		}
		ViewManager::Instance()->scroll(engineViewId, direction);
	} else if (direction == Direction::BOTTOM) {
		sf::Vector2f size = engineView.getSize();
		sf::Vector2f center = engineView.getCenter();
		const sf::Vector2i writePosition = this->devConsole->getWritePosition();
		float bottomOfView = center.y + size.y /2;
		if (writePosition.y < bottomOfView) {
			return;
		}
		ViewManager::Instance()->scroll(engineViewId, direction);
	}
}


void ConsoleManager::traverseHistory(sf::Event event) {

}


void ConsoleManager::addToCommand(unsigned int unicodeCharacter) {
	if (unicodeCharacter < 128  //if it's a character
	&& unicodeCharacter != 96 //tilde
	&& unicodeCharacter != 13 //return
	&& unicodeCharacter != 8) { // backspace
		this->command += static_cast<char>(unicodeCharacter);
	} else if (unicodeCharacter == 8) { //backspace
		this->command = this->command.substr(0, this->command.length() - 1);
	}
	this->devConsole->getCommandTIExt().setTextString(this->command);
}


std::vector<std::string>& ConsoleManager::splitString(const std::string& string, char delimiter, std::vector<std::string>& out) {
		std::istringstream iss(string);
		std::string item;
		while (std::getline(iss, item, delimiter)) {
			out.push_back(item);
		}
		if (out.empty()) {
			out.push_back(string); //If there is no delmiter, include the whole string
		}
		return out;
}
