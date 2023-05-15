#include "objects/tientities/engine/DevConsole.h" 

#include <memory>

#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/SpriteComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"
#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"
#include "managers/MessageManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"
#include "objects/assets/FontAsset.h"
#include "objects/components/PositionComponent.h" 
#include "objects/components/SpriteComponent.h" 
#include "objects/components/TextComponent.h" 
#include "objects/constants/MessageSubscriptions.h" 
#include "objects/tientities/common/SceneLayer.h"
#include "templates/MakeUnique.h"
#include "utils/ComponentSystems.h"

using namespace TIE;

DevConsole::DevConsole() :
	currentCommand(this->attachChild(make_unique<TIEntity>())),
	consoleHistorySceneLayer(dynamic_cast<SceneLayer&>(this->attachChild(make_unique<SceneLayer>()))),
	consoleHistory(this->consoleHistorySceneLayer.attachChild(make_unique<TIEntity>())) {
}


void DevConsole::initialize() {
	const FontAsset& font = AssetsManager::Instance()->getFont(ConfigManager::Instance()->getEngineFontName());

	// DevConsole Entity
	this->setName("DevConsole");

	// Command History SceneLayer
	//GlobalId consoleHistoryViewId = ViewManager::Instance()->addView(devConsoleBounds);
	//this->consoleHistorySceneLayer.setViewId(consoleHistoryViewId);
	this->consoleHistorySceneLayer.setViewId(ViewManager::Instance()->getEngineViewId());
	this->consoleHistorySceneLayer.setName("Console History Scene Layer");

	// Command History Entity
	this->consoleHistory.setName("Console History");
	TextComponent& historyTextComponent = TextComponentSystem::Instance()->addComponent(this->consoleHistory);
	historyTextComponent.setFont(font);
	historyTextComponent.setCharacterSize(this->fontSize);
	historyTextComponent.setTextAlignment(TextAlignment::TOP_LEFT);
	historyTextComponent.setString("Initialized Developer console.");
	historyTextComponent.setDrawn(true);

	// Command Input Entity
	this->currentCommand.setName("Current Command");

	TextComponent& currentCommandTextComponent = TextComponentSystem::Instance()->addComponent(this->currentCommand);
	currentCommandTextComponent.setFont(font);
	currentCommandTextComponent.setCharacterSize(this->fontSize);
	currentCommandTextComponent.setTextAlignment(TextAlignment::BOTTOM_LEFT);
	currentCommandTextComponent.setDrawn(true);

	this->setPosition();

	ComponentSystems::setDrawn(*this, false);

	MessageManager::Instance()->subscribe(MessageSubscriptions::WINDOW_SIZE_CHANGE, std::bind(&DevConsole::onWindowSizeChange, this));
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
	const sf::Vector2i& windowSize = WindowManager::Instance()->getWindowSize();
	this->textWritePosition.x = -windowSize.x/2;	
	this->textWritePosition.y = -windowSize.y/2;
}


TIEntity& DevConsole::getCurrentCommand() {
	return this->currentCommand;
}


void DevConsole::setPosition() {
	const sf::Vector2i& windowSize = WindowManager::Instance()->getWindowSize();

	PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(*this);
	sf::Vector2f position = sf::Vector2f(-(windowSize.x / 2), -(windowSize.y / 2));
	positionComponent.position = sf::Vector2f(position);

	SpriteComponent& spriteComponent = SpriteComponentSystem::Instance()->addComponent(*this);
	const sf::Texture& texture = AssetsManager::Instance()->getTexture("dev_console.png");
	spriteComponent.setTexture(texture);
	const sf::FloatRect& bounds = spriteComponent.getLocalBounds();
	float scalex = float(windowSize.x) / float(bounds.width);
	float scaley = float(windowSize.y/2.0f) / float(bounds.height);
	const sf::Vector2f scale = sf::Vector2f(scalex, scaley);
	spriteComponent.scale(scale);
	spriteComponent.setOrigin(0,0);

	sf::FloatRect devConsoleBounds = spriteComponent.getGlobalBounds();
	PositionComponent& currentCommandPositionComponent = PositionComponentSystem::Instance()->addComponent(this->currentCommand);
	currentCommandPositionComponent.position.x = devConsoleBounds.top;
	currentCommandPositionComponent.position.y = devConsoleBounds.height;
}


void DevConsole::onWindowSizeChange() {
	this->setPosition();
}
