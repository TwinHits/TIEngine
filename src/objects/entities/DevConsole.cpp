#include "objects/entities/DevConsole.h" 

#include <memory>
#include <string>

#include "componentsystems/TextComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/SpriteComponentSystem.h"
#include "managers/LogManager.h"
#include "managers/AssetsManager.h"
#include "managers/WindowManager.h"
#include "objects/components/SpriteComponent.h" 
#include "objects/components/TextComponent.h" 
#include "templates/MakeUnique.h"
#include "utils/ComponentSystems.h"

using namespace TIE;

DevConsole::DevConsole() :
	font(AssetsManager::Instance()->getFont("DevConsole.ttf")),
	currentCommand(this->attachChild(make_unique<TIEntity>())) {
}


void DevConsole::initialize() {
	this->setName("DevConsole");
	sf::Vector2i windowSize = TIE::WindowManager::Instance()->getWindowSize();
	sf::Vector2f position = sf::Vector2f(-(windowSize.y / 2), -(windowSize.x / 2));

	PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(*this);
	positionComponent.position = sf::Vector2f(position);

	SpriteComponent& spriteComponent = SpriteComponentSystem::Instance()->addComponent(*this);
	const sf::Texture& texture = AssetsManager::Instance()->getTexture("dev_console.png");
	const sf::Vector2u& textureSize = texture.getSize();
	spriteComponent.setTexture(texture, true);
	float scalex = float(windowSize.x) / float(textureSize.x);
	float scaley = float(windowSize.y/2.0f) / float(textureSize.y);
	const sf::Vector2f scale = sf::Vector2f(scalex, scaley);
	spriteComponent.scale(scale);
	sf::FloatRect size = spriteComponent.getLocalBounds();
	spriteComponent.setOrigin(0,0);

	// Command History
	TextComponent& historyTextComponent = TextComponentSystem::Instance()->addComponent(*this);
	historyTextComponent.setFont(this->font);
	historyTextComponent.setCharacterSize(this->fontSize);
	historyTextComponent.setTextAlignment(TextAlignment::TOP_LEFT);
	historyTextComponent.setString("Initialized Developer console.");

	// Command Input Entity
	TextComponent& currentCommandTextComponent = TextComponentSystem::Instance()->addComponent(this->currentCommand);
	PositionComponent& currentCommandPositionComponent = PositionComponentSystem::Instance()->addComponent(this->currentCommand);
	currentCommandTextComponent.setFont(this->font);
	currentCommandTextComponent.setCharacterSize(this->fontSize);
	currentCommandTextComponent.setTextAlignment(TextAlignment::TOP_LEFT);

	ComponentSystems::setDrawn(*this, false);
}


void DevConsole::update(const float delta) {
	//To get the messages to display in console, get not yet processed messages from the LogManager, turn them into tientities, and draw them. This happens every frame.
	while (!this->queueToDraw.empty()) {
		TextComponent* textComponent = this->getComponent<TextComponent>();
		if (textComponent != nullptr) {
			auto s = this->queueToDraw.front();
			textComponent->setString(textComponent->getString() + '\n' + s);
			this->queueToDraw.pop();
		}
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


TIEntity& DevConsole::getCurrentCommand() {
	return this->currentCommand;
}

