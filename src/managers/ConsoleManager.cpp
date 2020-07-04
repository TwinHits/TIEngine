#include "managers/ConsoleManager.h"

#include <algorithm>
#include <memory>
#include <queue>
#include <sstream>

#include "managers/ConfigManager.h"
#include "managers/LogManager.h"
#include "managers/SceneManager.h"
#include "managers/ScriptManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"
#include "managers/componentsystems/GraphicsComponentSystem.h"
#include "objects/constants/ConsoleCommands.h"
#include "templates/MakeUnique.h"

using namespace TIE;

ConsoleManager::ConsoleManager() {
	this->devConsole = &dynamic_cast<DevConsole&>(SceneManager::Instance()->getEngineLayer().attachChild(make_unique<DevConsole>()));
	this->devConsole->initialize();
}


void ConsoleManager::showConsole() {
	GraphicsComponentSystem::setDrawn(*this->devConsole, true);
}


void ConsoleManager::hideConsole() {
	GraphicsComponentSystem::setDrawn(*this->devConsole, false);
}


bool ConsoleManager::checkConsole() {
	return GraphicsComponentSystem::isDrawn(*this->devConsole);
}


void ConsoleManager::runCommand() {
	std::vector<std::string> commandArgs;
	this->splitString(this->command, ' ', commandArgs);
	const std::string& command = commandArgs.front();
	
	bool logCommand = true;
	if (command == ConsoleCommands::TEST) {
		LogManager::Instance()->command("Test Command Please Ignore.");
	} else if (command == ConsoleCommands::SCRIPT || command == ConsoleCommands::LOAD) {
		const std::string& scriptName = commandArgs.at(1);
		ScriptManager::Instance()->loadScript(scriptName);
	} else if (command == ConsoleCommands::PRINT) {
		if (!commandArgs.empty()) {
			const std::string& printCommand = commandArgs.at(1);
			if (printCommand == ConsoleCommands::SCENEGRAPH) {
				this->printSceneGraph(SceneManager::Instance()->getSceneGraphRoot());
			}
		}
	} else if (command == ConsoleCommands::CLEAR) {
		this->clearConsoleHistory();
		logCommand = false;
	} else if (command == ConsoleCommands::CLEARLOG) {
		this->clearDebugLog();
		logCommand = false;
	} else {
		LogManager::Instance()->command("Unknown command.");
	}

	if (logCommand) {
   		LogManager::Instance()->command(this->command);
	}
	this->commandHistory.push_back(this->command);
	this->command = "";
	this->historyIndex = commandHistory.end();
}


const std::string& ConsoleManager::getCommand() {
	return this->command;
}


void ConsoleManager::setDevConsole(std::unique_ptr<DevConsole> devConsole) {
	this->devConsole->setRemove(true);
	SceneLayer& engineLayer = SceneManager::Instance()->getEngineLayer();
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


void ConsoleManager::traverseDownHistory() {
	if (this->historyIndex != this->commandHistory.end()) {
		this->historyIndex++;
		if (this->historyIndex != this->commandHistory.end()) {
			this->command = *(this->historyIndex);
			this->devConsole->getComponent<TextComponent>()->setString(this->command);
		} else {
			this->command = "";
			this->devConsole->getComponent<TextComponent>()->setString(this->command);
		}
	}
}


void ConsoleManager::traverseUpHistory() {
	if (this->historyIndex != this->commandHistory.begin()) {
		this->historyIndex--;
		this->command = *(this->historyIndex);
		this->devConsole->getComponent<TextComponent>()->setString(this->command);
	}
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
	this->devConsole->getComponent<TextComponent>()->setString(this->command);
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


void ConsoleManager::printSceneGraph(TIEntity& tientity) {
	LogManager::Instance()->command(tientity.getName());
	for (auto& child : tientity.getChildren()) {
		this->printSceneGraph(*child);
	}
}

void TIE::ConsoleManager::clearConsoleHistory() {
	for (auto& child : this->devConsole->getChildren()) {
		child->setRemove(true);
	}
		this->devConsole->resetWritePosition();
}

void TIE::ConsoleManager::clearDebugLog() {
	this->clearConsoleHistory();
	LogManager::Instance()->clearLog();
	LogManager::Instance()->info("Logs cleared by console command.");
}
