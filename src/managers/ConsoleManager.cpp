#include "managers/ConsoleManager.h"

#include <algorithm>
#include <memory>
#include <queue>
#include <sstream>

#include "componentsystems/SpriteComponentSystem.h"
#include "managers/ConfigManager.h"
#include "managers/WorldManager.h"
#include "managers/LogManager.h"
#include "managers/SceneManager.h"
#include "managers/ScriptManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"
#include "objects/components/TextComponent.h"
#include "objects/constants/ConsoleCommands.h"
#include "templates/MakeUnique.h"
#include "utils/StringHelpers.h"
#include "utils/Graphics.h"

using namespace TIE;

bool ConsoleManager::initialize() {
	this->devConsole = &dynamic_cast<DevConsole&>(SceneManager::Instance()->getEngineLayer().attachChild(make_unique<DevConsole>()));
	this->devConsole->initialize();
	return true;
}


void ConsoleManager::showConsole() {
	Graphics::setDrawn(*this->devConsole, true);
}


void ConsoleManager::hideConsole() {
	Graphics::setDrawn(*this->devConsole, false);
}


bool ConsoleManager::checkConsole() {
	return Graphics::isDrawn(*this->devConsole);
}


void ConsoleManager::runCommand() {
	std::vector<std::string> commandArgs = String::slice(this->input, ' ', 0);
	const std::string& command = commandArgs.front();
	
   	LogManager::Instance()->command(this->input);
	this->commandHistory.push_back(this->input);
	this->historyIndex = commandHistory.end();

	if (command == ConsoleCommands::TEST) {
		LogManager::Instance()->command("Test Command Please Ignore.");
	} else if (command == ConsoleCommands::QUIT) {
		WindowManager::Instance()->removeWindow();
	} else if (command == ConsoleCommands::SCRIPT || command == ConsoleCommands::LOAD) {
		const std::string& scriptName = commandArgs.at(1);
		ScriptManager::Instance()->loadScript(scriptName);
	} else if (command == ConsoleCommands::PRINT) {
		if (commandArgs.size() > 1) {
			const std::string& printCommand = commandArgs.at(1);
			if (printCommand == ConsoleCommands::SCENEGRAPH) {
				this->printSceneGraph(SceneManager::Instance()->getSceneGraphRoot());
			}
		}
	} else if (command == ConsoleCommands::CLEAR) {
		this->clearConsoleHistory();
	} else if (command == ConsoleCommands::CLEARLOG) {
		this->clearDebugLog();
	} else if (command == ConsoleCommands::SHOW) {
		this->showGridGuide();
	} else if (command == ConsoleCommands::SPAWN) {
		const std::string& name = commandArgs.at(1);
		WorldManager::Instance()->spawnTIEntity(name);
	} else {
		LogManager::Instance()->command("Unknown command.");
	}

	this->input = "";
}


const std::string& ConsoleManager::getInput() {
	return this->input;
}


void ConsoleManager::setDevConsole(std::unique_ptr<DevConsole> devConsole) {
	this->devConsole->setRemove(true);
	SceneLayer& engineLayer = SceneManager::Instance()->getEngineLayer();
	this->devConsole = &dynamic_cast<DevConsole&>(engineLayer.attachChild(std::move(devConsole)));
}


void ConsoleManager::scroll(Direction direction) {
	sf::View& engineView = ViewManager::Instance()->getEngineView();
	if (direction == Direction::TOP) {
		sf::Vector2f center = engineView.getCenter();
		if (center.y == 0) {
			return;		
		}
	} else if (direction == Direction::BOTTOM) {
		sf::Vector2f size = engineView.getSize();
		sf::Vector2f center = engineView.getCenter();
		const sf::Vector2i writePosition = this->devConsole->getWritePosition();
		float bottomOfView = center.y + size.y /2;
		if (writePosition.y < bottomOfView) {
			return;
		}
	}
}


void ConsoleManager::traverseDownHistory() {
	if (this->historyIndex != this->commandHistory.end()) {
		this->historyIndex++;
		if (this->historyIndex != this->commandHistory.end()) {
			this->input = *(this->historyIndex);
			this->devConsole->getComponent<TextComponent>()->setString(this->input);
		} else {
			this->input = "";
			this->devConsole->getComponent<TextComponent>()->setString(this->input);
		}
	}
}


void ConsoleManager::traverseUpHistory() {
	if (this->historyIndex != this->commandHistory.begin()) {
		this->historyIndex--;
		this->input = *(this->historyIndex);
		this->devConsole->getComponent<TextComponent>()->setString(this->input);
	}
}


void ConsoleManager::addToInput(unsigned int unicodeCharacter) {
	if (unicodeCharacter < 128  // if it's a character
	&& unicodeCharacter != 126 // tilde
	&& unicodeCharacter != 96 // back tick/open quote
	&& unicodeCharacter != 13 // return
	&& unicodeCharacter != 8) { // backspace
		this->input += static_cast<char>(unicodeCharacter);
	} else if (unicodeCharacter == 8) { //backspace
		this->input = this->input.substr(0, this->input.length() - 1);
	}
	this->devConsole->getComponent<TextComponent>()->setString(this->input);
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
	LogManager::Instance()->clearQueueToDraw();
}


void TIE::ConsoleManager::clearDebugLog() {
	this->clearConsoleHistory();
	LogManager::Instance()->clearLog();
	LogManager::Instance()->info("Logs cleared by console command.");
}


void TIE::ConsoleManager::showGridGuide() {
	WorldManager::Instance()->showGridGuide(true);
}
