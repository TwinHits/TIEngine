#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"

#include "objects/drawables/MousePtrCoords.h"

using namespace TIE;

MousePtrCoords::MousePtrCoords() : 
	font(AssetsManager::Instance()->getFont("DevConsole.ttf")) {

	sf::Text text = this->getText();
	text.setString("0, 0");
	text.setFont(font);
	text.setCharacterSize(14);

	sf::Vector2f mouseWindowPosition = inputManager->getMouseWindowPosition();
	this->setPosition(mouseWindowPosition.x + 20, mouseWindowPosition.y);
	this->setDrawn(ConfigManager::Instance()->getShowMousePtrCoords());
	this->setType("Mouse Coords");
}


MousePtrCoords::~MousePtrCoords() {

}


void MousePtrCoords::updateSelf(const float delta) {
	if (this->getDrawn()) {
		sf::Vector2f mouseWorldPosition = inputManager->getMouseWorldPosition();
		sf::Vector2f mouseWindowPosition = inputManager->getMouseWindowPosition();
		this->getText().setString(std::to_string(int(mouseWorldPosition.x)) + ", " + std::to_string(int(mouseWorldPosition.y)));
		this->setPosition(mouseWindowPosition.x + 20, mouseWindowPosition.y);
	}
}
