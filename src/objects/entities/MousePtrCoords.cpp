#include "objects/entities/MousePtrCoords.h"

#include "componentsystems/GraphicsComponentSystem.h"
#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"

using namespace TIE;

MousePtrCoords::MousePtrCoords() :
	font(AssetsManager::Instance()->getFont("DevConsole.ttf")) {
}


void MousePtrCoords::initialize() {
	this->setName("MousePtrCoords");

	sf::Vector2f mouseWindowPosition = this->inputManager->getMouseWindowPosition();

	TextComponent* textComponent = GraphicsComponentSystem::addTextComponent(*this);
	textComponent->setString("0, 0");
	textComponent->setFont(font);
	textComponent->setCharacterSize(14);
	textComponent->setPosition(mouseWindowPosition.x + 20, mouseWindowPosition.y);
	textComponent->setDrawn(ConfigManager::Instance()->getShowMousePtrCoords());
}


void MousePtrCoords::update(const float delta) {
	if (GraphicsComponentSystem::isDrawn(*this)) {
		TextComponent* textComponent = this->getComponent<TextComponent>();
		sf::Vector2f mouseWorldPosition = this->inputManager->getMouseWorldPosition();
		sf::Vector2f mouseWindowPosition = this->inputManager->getMouseWindowPosition();
		textComponent->setString(std::to_string(int(mouseWorldPosition.x)) + ", " + std::to_string(int(mouseWorldPosition.y)));
		textComponent->setString(textComponent->getString() + "\n" + (std::to_string(int(mouseWindowPosition.x)) + ", " + std::to_string(int(mouseWindowPosition.y))));
		textComponent->setPosition(mouseWindowPosition.x + 20, mouseWindowPosition.y);
	}
}
