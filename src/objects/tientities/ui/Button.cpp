#include "objects/tientities/ui/Button.h"

#include <SFML/Graphics.hpp>

#include "componentsystems/ClickableComponentSystem.h"
#include "componentsystems/MessagesComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/ShapeComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"
#include "enumeration/TextAlignment.h"
#include "managers/MessageManager.h"
#include "objects/GlobalId.h"

using namespace TIE;

Button::Button(const std::string text, const sf::Vector2f& position, const sf::Vector2f& size, std::function<void(Message&)> onClick) {
    this->setName(text + " Button");

    PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(*this);
    positionComponent.position = position;

    ShapeComponent& shapeComponent = ShapeComponentSystem::Instance()->addComponent(*this);
    sf::RectangleShape& rectangleShape = shapeComponent.addRectangleShape();
    rectangleShape.setSize(size);
    rectangleShape.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
    rectangleShape.setOutlineThickness(2);
    rectangleShape.setOutlineColor(sf::Color::White);
    rectangleShape.setFillColor(sf::Color::Transparent);

    TextComponent& textComponent = TextComponentSystem::Instance()->addComponent(*this);
    textComponent.setTextAlignment(TextAlignment::CENTER);
    textComponent.setString(text);
    textComponent.setCharacterSize(16);

    ClickableComponentSystem::Instance()->setOnClick(*this, onClick);
}
