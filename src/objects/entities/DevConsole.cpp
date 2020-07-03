#include <memory>
#include <string>

#include "managers/componentsystems/GraphicsComponentSystem.h"
#include "managers/LogManager.h"
#include "managers/AssetsManager.h"
#include "managers/WindowManager.h"

#include "objects/components/SpriteComponent.h" 
#include "objects/components/TextComponent.h" 
#include "objects/entities/DevConsole.h" 

#include "templates/MakeUnique.h"

using namespace TIE;

DevConsole::DevConsole() :
	font(AssetsManager::Instance()->getFont("DevConsole.ttf")),
	currentCommand(dynamic_cast<TIEntity&>(this->attachChild(make_unique<TIEntity>()))) {

}

void DevConsole::initialize() {
	this->setName("DevConsole");
	sf::Vector2i windowSize = TIE::WindowManager::Instance()->getWindowSize();
	textWritePosition.x = -windowSize.x/2;	
	textWritePosition.y = -windowSize.y/2;
	
	sf::Texture& texture = AssetsManager::Instance()->getTexture("dev_console.png");
	sf::Vector2u size = texture.getSize();

	SpriteComponent* spriteComponent = GraphicsComponentSystem::addSpriteComponent(*this);
	spriteComponent->setTexture(texture);
	spriteComponent->setTextureRect(sf::Rect<int>(0, 0, size.x, size.y));
	spriteComponent->setOrigin(size.x/2, size.y/2);
	spriteComponent->setPosition(sf::Vector2f(0,0));
	spriteComponent->setRotation(0);
	spriteComponent->setScale(1,1);

	TextComponent* textComponent = GraphicsComponentSystem::addTextComponent(*this);
	textComponent->setFont(font);
	textComponent->setCharacterSize(fontSize);
	textComponent->setPosition(-(windowSize.x/2), windowSize.y/2 - fontSize);
}


void DevConsole::update(const float delta) {
	//To get the messages to display in console, get not yet processed messages from the LogManager, turn them into scene texts, and draw them. This happens every frame.

	std::queue<std::string>& queue = LogManager::Instance()->getQueueToDraw();

	while (!queue.empty()) {
		auto s = queue.front();

		std::unique_ptr<TIEntity> entity = make_unique<TIEntity>();
		entity->setName("DevConsoleHistoryItem");
		TextComponent* textComponent = GraphicsComponentSystem::addTextComponent(*entity);
		textComponent->setString(s);
		textComponent->setFont(font);
		textComponent->setCharacterSize(fontSize);
		textComponent->setPosition(textWritePosition.x, textWritePosition.y);
		textComponent->setDrawn(true);

		this->textWritePosition.y += fontSize;

		this->attachChild(std::move(entity));
		queue.pop();
	}
}


const sf::Vector2i& DevConsole::getWritePosition() {
	return this->textWritePosition;
}


TIEntity& DevConsole::getCommandText() {
	return this->currentCommand;
}
