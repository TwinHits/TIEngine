#include "objects/entities/DevConsole.h" 

#include <memory>
#include <string>

#include "componentsystems/TextComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/ShapeComponentSystem.h"
#include "componentsystems/SpriteComponentSystem.h"
#include "managers/LogManager.h"
#include "managers/AssetsManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"
#include "objects/SceneLayer.h"
#include "objects/components/SpriteComponent.h" 
#include "objects/components/TextComponent.h" 
#include "templates/MakeUnique.h"
#include "utils/ComponentSystems.h"

using namespace TIE;

DevConsole::DevConsole() :
	font(AssetsManager::Instance()->getFont("DevConsole.ttf")),
	currentCommand(this->attachChild(make_unique<TIEntity>())),
	consoleHistorySceneLayer(dynamic_cast<SceneLayer&>(this->attachChild(make_unique<SceneLayer>()))),
	consoleHistory(this->consoleHistorySceneLayer.attachChild(make_unique<TIEntity>())) {
}


void DevConsole::initialize() {
	sf::Vector2i windowSize = TIE::WindowManager::Instance()->getWindowSize();

	// DevConsole Entity
	this->setName("DevConsole");

	PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(*this);
	sf::Vector2f position = sf::Vector2f(-(windowSize.x / 2), -(windowSize.y / 2));
	positionComponent.position = sf::Vector2f(position);

	SpriteComponent& spriteComponent = SpriteComponentSystem::Instance()->addComponent(*this);
	const sf::Texture& texture = AssetsManager::Instance()->getTexture("dev_console.png");
	const sf::Vector2u& textureSize = texture.getSize();
	spriteComponent.setTexture(texture, true);
	float scalex = float(windowSize.x) / float(textureSize.x);
	float scaley = float(windowSize.y/2.0f) / float(textureSize.y);
	const sf::Vector2f scale = sf::Vector2f(scalex, scaley);
	spriteComponent.scale(scale);
	spriteComponent.setOrigin(0,0);

	sf::FloatRect devConsoleBounds = spriteComponent.getGlobalBounds();

	// Command History SceneLayer
	//GlobalId consoleHistoryViewId = ViewManager::Instance()->addView(devConsoleBounds);
	//this->consoleHistorySceneLayer.setViewId(consoleHistoryViewId);
	this->consoleHistorySceneLayer.setViewId(ViewManager::Instance()->getEngineViewId());
	this->consoleHistorySceneLayer.setLayer(SceneLayer::Layer::ENGINE);
	this->consoleHistorySceneLayer.setName("Console History Scene Layer");

	// Command History Entity
	this->consoleHistory.setName("Console History");
	TextComponent& historyTextComponent = TextComponentSystem::Instance()->addComponent(this->consoleHistory);
	historyTextComponent.setFont(this->font);
	historyTextComponent.setCharacterSize(this->fontSize);
	historyTextComponent.setTextAlignment(TextAlignment::TOP_LEFT);
	historyTextComponent.setString("Initialized Developer console.");
	historyTextComponent.setDrawn(true);

	// Command Input Entity
	this->currentCommand.setName("Current Command");

	PositionComponent& currentCommandPositionComponent = PositionComponentSystem::Instance()->addComponent(this->currentCommand);
	currentCommandPositionComponent.position.x = devConsoleBounds.top;
	currentCommandPositionComponent.position.y = devConsoleBounds.height;

	TextComponent& currentCommandTextComponent = TextComponentSystem::Instance()->addComponent(this->currentCommand);
	currentCommandTextComponent.setFont(this->font);
	currentCommandTextComponent.setCharacterSize(this->fontSize);
	currentCommandTextComponent.setTextAlignment(TextAlignment::BOTTOM_LEFT);
	currentCommandTextComponent.setDrawn(true);

	ComponentSystems::setDrawn(*this, false);
}


void DevConsole::update(const float delta) {
	//To get the messages to display in console, get not yet processed messages from the LogManager, turn them into tientities, and draw them. This happens every frame.
	while (!this->queueToDraw.empty()) {
		TextComponent* textComponent = this->consoleHistory.getComponent<TextComponent>();
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

