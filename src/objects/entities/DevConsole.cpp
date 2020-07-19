#include "objects/entities/DevConsole.h" 

#include <memory>
#include <string>

#include "componentsystems/GraphicsComponentSystem.h"
#include "managers/LogManager.h"
#include "managers/AssetsManager.h"
#include "managers/WindowManager.h"
#include "objects/components/SpriteComponent.h" 
#include "objects/components/TextComponent.h" 
#include "templates/MakeUnique.h"

using namespace TIE;

DevConsole::DevConsole() :
	font(AssetsManager::Instance()->getFont("DevConsole.ttf")),
	currentCommand(this->attachChild(make_unique<TIEntity>())) {
}


void DevConsole::initialize() {
	this->setName("DevConsole");
	sf::Vector2i windowSize = TIE::WindowManager::Instance()->getWindowSize();
	textWritePosition.x = -windowSize.x/2;	
	textWritePosition.y = -windowSize.y/2;

	SpriteComponent* spriteComponent = GraphicsComponentSystem::addSpriteComponent(*this);
	sf::Texture& texture = AssetsManager::Instance()->getTexture("dev_console.png");
	spriteComponent->setTexture(texture, true);
	sf::FloatRect size = spriteComponent->getLocalBounds();
	spriteComponent->setOrigin(size.width/2, size.height);

	TextComponent* textComponent = GraphicsComponentSystem::addTextComponent(*this);
	textComponent->setFont(font);
	textComponent->setCharacterSize(fontSize);
	textComponent->setPosition(-(windowSize.x / 2) + 3, -fontSize - 5);
}


void DevConsole::update(const float delta) {
	//To get the messages to display in console, get not yet processed messages from the LogManager, turn them into scene texts, and draw them. This happens every frame.
	while (!this->queue.empty()) {
		auto s = this->queue.front();

		TIEntity& entity = this->attachChild(make_unique<TIEntity>());
		entity.setName("DevConsoleHistoryItem");
		TextComponent* textComponent = GraphicsComponentSystem::addTextComponent(entity);
		textComponent->setString(s);
		textComponent->setFont(font);
		textComponent->setCharacterSize(fontSize);
		textComponent->setPosition(textWritePosition.x, textWritePosition.y);
		this->textWritePosition.y += fontSize;
		textComponent->setDrawn(true);

		this->queue.pop();
	}
}


const sf::Vector2i& DevConsole::getWritePosition() {
	return this->textWritePosition;
}

void DevConsole::setWritePosition(const sf::Vector2i& position) {
	this->textWritePosition = position;
}

void DevConsole::resetWritePosition() {
	sf::Vector2i windowSize = TIE::WindowManager::Instance()->getWindowSize();
	this->textWritePosition.x = -windowSize.x/2;	
	this->textWritePosition.y = -windowSize.y/2;
}


TIEntity& DevConsole::getCommandText() {
	return this->currentCommand;
}

