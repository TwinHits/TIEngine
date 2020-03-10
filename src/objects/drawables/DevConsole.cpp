#include <string>

#include "managers/LogManager.h"
#include "managers/AssetsManager.h"
#include "managers/WindowManager.h"

#include "objects/drawables/DevConsole.h" 

#include "templates/MakeUnique.h"

using namespace TIE;

DevConsole::DevConsole() : font(AssetsManager::Instance()->getFont("DevConsole.ttf")),
	currentCommand(dynamic_cast<TIExt&>(this->attachChild(make_unique<TIExt>()))) {
	sf::Vector2i windowSize = TIE::WindowManager::Instance()->getWindowSize();

	textWritePosition.x = -windowSize.x/2;	
	textWritePosition.y = -windowSize.y/2;
	
	sf::Texture& texture = AssetsManager::Instance()->getTexture("dev_console.png");
	sf::Vector2u size = texture.getSize();

	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(sf::Rect<int>(0, 0, size.x, size.y));
	this->sprite.setOrigin(size.x/2, size.y/2);

	this->setPosition(sf::Vector2f(0,0));
	this->setRotation(0);
	this->setScale(1,1);
	this->setDrawn(false);
	this->setCollidable(false);
	
	this->currentCommand.getText().setFont(font);
	this->currentCommand.getText().setCharacterSize(fontSize);
	this->currentCommand.setDrawn(true);
	this->currentCommand.getText().setPosition(-(windowSize.x/2), windowSize.y/2 - fontSize);

	this->setType("Default Dev Console.");
}


DevConsole::~DevConsole() {

}	


void DevConsole::updateSelf(const float delta) {
	//To get the messages to display in console, get not yet processed messages from the LogManager, turn them into scene texts, and draw them. This happens every frame.

	std::queue<std::string>& queue = LogManager::Instance()->getQueueToDraw();

	while (!queue.empty()) {
		auto s = queue.front();

		std::unique_ptr<TIExt> tiext = make_unique<TIExt>();
		tiext->getText().setString(s);
		tiext->getText().setFont(font);
		tiext->getText().setCharacterSize(fontSize);
		tiext->getText().setPosition(textWritePosition.x, textWritePosition.y);
		tiext->setDrawn(true);

		textWritePosition.y += fontSize;

		this->attachChild(std::move(tiext));

		queue.pop();
	}
}


const sf::Vector2i& DevConsole::getWritePosition() {
	return this->textWritePosition;
}


TIExt& DevConsole::getCommandTIExt() {
	return this->currentCommand;
}


void DevConsole::drawSelf(sf::RenderTarget& window, sf::RenderStates states) const {
	window.draw(this->getSprite(), states);
}
