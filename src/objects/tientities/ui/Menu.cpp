#include "objects/tientities/ui/Menu.h"

#include <SFML/Graphics.hpp>

#include "componentsystems/PositionComponentSystem.h"
#include "managers/InputManager.h"
#include "objects/Message.h"
#include "utils/ComponentSystems.h"


using namespace TIE;

void Menu::onClick(Message& message) {
    this->show = !this->show;
    if (this->show) {
        const sf::Vector2f& clickPosition = InputManager::Instance()->getMouseWindowPosition();
        PositionComponentSystem::Instance()->setPosition(*this, clickPosition);
    }
    ComponentSystems::setDrawn(*this, this->show);
}
