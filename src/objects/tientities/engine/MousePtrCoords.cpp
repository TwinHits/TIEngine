#include "objects/tientities/engine/MousePtrCoords.h"

#include <sstream>

#include <SFML/Graphics.hpp>

#include "componentsystems/TextComponentSystem.h"
#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"
#include "utils/ComponentSystems.h"

using namespace TIE;

MousePtrCoords::MousePtrCoords() {
	this->setName("MousePtrCoords");

	sf::Vector2f mouseWindowPosition = this->inputManager->getMouseWindowPosition();

	TextComponent& textComponent = this->addComponent<TextComponent>();
	textComponent.setString("0, 0");
	textComponent.setFont(AssetsManager::Instance()->getFont(ConfigManager::Instance()->getEngineFontName()));
	textComponent.setCharacterSize(18);
	textComponent.setPosition(mouseWindowPosition.x + 20, mouseWindowPosition.y);
	textComponent.setDrawn(ConfigManager::Instance()->getShowMousePtrCoords());
}


void MousePtrCoords::update(const float delta) {
	if (ComponentSystems::isDrawn(*this)) {
		if (this->cachedMouseWorldPostion != this->inputManager->getMouseWorldPosition() || this->cachedMouseWindowPostion == this->inputManager->getMouseWindowPosition()) {
			this->cachedMouseWorldPostion = this->inputManager->getMouseWorldPosition();
			this->cachedMouseWindowPostion = this->inputManager->getMouseWindowPosition();
			TextComponent* textComponent = this->getComponent<TextComponent>();

			std::stringstream ss;
			ss << int(this->cachedMouseWorldPostion.x) << ", " << int(this->cachedMouseWorldPostion.y);
			ss << std::endl;
			ss << int(this->cachedMouseWindowPostion.x) << ", " << int(this->cachedMouseWindowPostion.y);

			textComponent->setString(ss.str());
			textComponent->setPosition(this->cachedMouseWindowPostion.x + 20, this->cachedMouseWindowPostion.y);
		}
	}
}
