#include <string>

#include "managers/LogManager.h"
#include "managers/AssetsManager.h"
#include "managers/InputManager.h"
#include "managers/HashManager.h"
#include "managers/WindowManager.h"

#include "objects/drawables/DevConsole.h" 

using namespace TIE;

DevConsole::DevConsole() : font(AssetsManager::Instance()->getFont("DevConsole.ttf")) {
	sf::Vector2i windowSize = TIE::WindowManager::Instance()->getWindowSize();

	textWritePosition.x = -windowSize.x/2;	
	textWritePosition.y = -windowSize.y/2;

	this->sprite.setPosition(sf::Vector2f(-(windowSize.x/2), -(windowSize.y/2)));
	this->sprite.setTexture(AssetsManager::Instance()->getTexture("missing_texture.png"));
	this->setDraw(false);
	this->setCollidable(false);
	
	//Set the currentCommand for drawing only. Maybe later combine with processing?
	this->currentCommand.getText().setFont(font);
	this->currentCommand.getText().setCharacterSize(fontSize);

	this->currentCommand.getText().setPosition(-(windowSize.x/2), windowSize.y/2 - fontSize);
}


DevConsole::~DevConsole() {

}	


const std::vector<SceneText>& DevConsole::getCommandHistory() {
	return commandHistory;
}


const SceneText& DevConsole::getCurrentCommand() {
	return currentCommand;
}


int DevConsole::runClientCommand(const std::string& command) {
	LogManager::Instance()->logWarn("No client DevConsole defined.");
	return 1;
}


void DevConsole::processCommand(const std::string& command) {
   	LogManager::Instance()->logCommand(command);

	if (command == "test") {
		LogManager::Instance()->logCommand("Test Command Please Ignore.");
	}
	//Run client commands
	else if (this->runClientCommand(command) == 1) {
		LogManager::Instance()->logCommand("Unknown command.");
	}
}	


void DevConsole::update(const float delta) {
	//To get the messages to display in console, get not yet processed messages from the LogManager, turn them into scene texts, and draw them. This happens every frame.

	auto textEntered = InputManager::Instance()->getTextEntered();
	currentCommand.getText().setString(textEntered);

	std::queue<std::string>& queue = LogManager::Instance()->getQueueToDraw();

	SceneText text;
	while (!queue.empty()) {
		auto s = queue.front();

		text.getText().setString(s);
		text.getText().setFont(font);
		text.getText().setCharacterSize(fontSize);
		text.getText().setPosition(textWritePosition.x, textWritePosition.y);

		textWritePosition.y += fontSize;
		commandHistory.push_back(text);	

		queue.pop();
	}

}


const sf::Vector2i& DevConsole::getWritePosition() {
	return this->textWritePosition;
}
