#include "objects/entities/MousePtrCoords.h"

#include "componentsystems/TextComponentSystem.h"
#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"
#include "utilities/Graphics.h"

using namespace TIE;

MousePtrCoords::MousePtrCoords() :
	font(AssetsManager::Instance()->getFont("DevConsole.ttf")) {
}


void MousePtrCoords::initialize() {
	this->setName("MousePtrCoords");

	sf::Vector2f mouseWindowPosition = this->eventsManager->getMouseWindowPosition();

	TextComponent& textComponent = TextComponentSystem::Instance()->addComponent(*this);
	textComponent.setString("0, 0");
	textComponent.setFont(font);
	textComponent.setCharacterSize(14);
	textComponent.setPosition(mouseWindowPosition.x + 20, mouseWindowPosition.y);
	textComponent.setDrawn(ConfigManager::Instance()->getShowMousePtrCoords());
}


void MousePtrCoords::update(const float delta) {
	if (Graphics::isDrawn(*this)) {
		TextComponent* textComponent = this->getComponent<TextComponent>();
		sf::Vector2f mouseWorldPosition = this->eventsManager->getMouseWorldPosition();
		sf::Vector2f mouseWindowPosition = this->eventsManager->getMouseWindowPosition();
		textComponent->setString(std::to_string(int(mouseWorldPosition.x)) + ", " + std::to_string(int(mouseWorldPosition.y)));
		textComponent->setString(textComponent->getString() + "\n" + (std::to_string(int(mouseWindowPosition.x)) + ", " + std::to_string(int(mouseWindowPosition.y))));
		textComponent->setPosition(mouseWindowPosition.x + 20, mouseWindowPosition.y);
	}
}
