#include "objects/entities/MousePtrCoords.h"

#include <sstream>

#include <SFML/Graphics.hpp>

#include "componentsystems/TextComponentSystem.h"
#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"
#include "utils/Graphics.h"

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
		if (this->cachedMouseWorldPostion != this->eventsManager->getMouseWorldPosition() || this->cachedMouseWindowPostion == this->eventsManager->getMouseWindowPosition()) {
			this->cachedMouseWorldPostion = this->eventsManager->getMouseWorldPosition();
			this->cachedMouseWindowPostion = this->eventsManager->getMouseWindowPosition();
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
