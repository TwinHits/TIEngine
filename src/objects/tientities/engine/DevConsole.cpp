#include "objects/tientities/engine/DevConsole.h" 

#include <memory>

#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/SpriteComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"
#include "constants/MessageSubscriptions.h" 
#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"
#include "managers/LogManager.h"
#include "managers/MessageManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"
#include "objects/assets/FontAsset.h"
#include "objects/components/PositionComponent.h" 
#include "objects/components/SpriteComponent.h" 
#include "objects/components/TextComponent.h" 
#include "objects/tientities/common/SceneLayer.h"
#include "templates/MakeUnique.h"
#include "utils/ComponentSystems.h"
#include "utils/String.h"

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
	this->setPosition();
	this->setLineCharacterLimit();

	// Command History SceneLayer
	// Clipping the dev console is supposedly possible through using views,
	// But as is the text is being scaled by the scaling of the viewport
	// SFML 3.0 adds support for scissoring, which does exactly what I want it to do.
	this->consoleHistorySceneLayer.setName("Console History Scene Layer");
	const sf::Vector2i& windowSize = WindowManager::Instance()->getWindowSize();
	GlobalId consoleHistoryViewId = ViewManager::Instance()->addView(sf::FloatRect(0, 0, 1.0f, 1.0f), sf::FloatRect(0, 0, 1.0f, 0.5f));
	this->consoleHistorySceneLayer.setViewId(consoleHistoryViewId);

	// Command History Entity
	this->consoleHistory.setName("Console History");
	TextComponent& historyTextComponent = TextComponentSystem::Instance()->addComponent(
		this->consoleHistory, 
		font,
		"Initialized Developer console.",
		this->fontSize,
		TextAlignment::TOP_LEFT,
		true
	);

	// Command Input Entity
	this->currentCommand.setName("Current Command");
	TextComponent& currentCommandTextComponent = TextComponentSystem::Instance()->addComponent(
		this->currentCommand,
		font,
		"",
		this->fontSize,
		TextAlignment::BOTTOM_LEFT,
		true
	);

	ComponentSystems::setDrawn(*this, false);

	MessageManager::Instance()->subscribe(MessageSubscriptions::WINDOW_SIZE_CHANGE, std::bind(&DevConsole::onWindowSizeChange, this));
	MessageManager::Instance()->subscribe(MessageSubscriptions::LOG_ENTERED, std::bind(&DevConsole::onLogEntered, this));
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
	spriteComponent.setScale(scale);
	spriteComponent.setOrigin(0,0);

	sf::FloatRect devConsoleBounds = spriteComponent.getGlobalBounds();
	PositionComponent& currentCommandPositionComponent = PositionComponentSystem::Instance()->addComponent(this->currentCommand);
	currentCommandPositionComponent.position.x = devConsoleBounds.top;
	currentCommandPositionComponent.position.y = devConsoleBounds.height;
}


void DevConsole::setLineCharacterLimit() {
	const sf::Vector2i& windowSize = WindowManager::Instance()->getWindowSize();
	this->maxLineLength = windowSize.x / (this->fontSize / 2);
}


void DevConsole::onWindowSizeChange() {
	this->setPosition();
	this->setLineCharacterLimit();
}


void DevConsole::onLogEntered() {
    TextComponent* textComponent = this->consoleHistory.getComponent<TextComponent>();
    if (textComponent != nullptr) {
        const std::string& logEntered = LogManager::Instance()->getLastLogEntered();
        std::vector<std::string> breakNewLines;
        breakNewLines = String::split(logEntered, '\n', breakNewLines);

        std::vector<std::string> lines;
        for (auto& breakNewLine : breakNewLines) {
			if (breakNewLine.length() > this->maxLineLength) {
				std::string line;

				std::vector<std::string> words;
				words = String::split(breakNewLine, ' ', words);
				for (auto& word : words) {
					if ((line + " " + word).length() > this->maxLineLength) {
						lines.push_back(line);
						line = word;
					} else {
						line = line + word + " ";
					}
				}
				lines.push_back(line);
			} else {
				lines.push_back(breakNewLine);
			}
        }

        for (const std::string& line : lines) {
            textComponent->setString(textComponent->getString() + '\n' + line);
        }

    }
}
