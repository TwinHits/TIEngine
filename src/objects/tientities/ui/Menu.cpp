#include "objects/tientities/ui/Menu.h"

#include <SFML/Graphics.hpp>

#include "componentsystems/PositionComponentSystem.h"
#include "managers/InputManager.h"
#include "utils/ComponentSystems.h"


using namespace TIE;

void Menu::onClick(Message& message) {
    const bool drawn = ComponentSystems::isDrawn(*this);
    if (!drawn) {
        const sf::Vector2f& clickPosition = InputManager::Instance()->getMouseWindowPosition();
        PositionComponentSystem::Instance()->setPosition(*this, clickPosition);
    }
    ComponentSystems::setDrawn(*this, !drawn);
}
