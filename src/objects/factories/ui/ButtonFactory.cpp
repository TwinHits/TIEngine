#include "objects/factories/ui/ButtonFactory.h"

#include "componentsystems/ClickableComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/ShapeComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"
#include "objects/ScriptTableReader.h"
#include "objects/factories/ui/UIElementFactory.h"

using namespace TIE;

ButtonFactory::ButtonFactory(): UIElementFactory() {}


ButtonFactory::ButtonFactory(const sol::table& definition): UIElementFactory(definition) {
    const ScriptTableReader& reader = this->getReader();
    this->text = reader.get<std::string>("text", this->text);
    this->onClickId = reader.get<GlobalId>("onClick", this->onClickId);
}


ButtonFactory& ButtonFactory::setPosition(const sf::Vector2f& position) {
    this->position = position;
    return *this;
}


ButtonFactory& ButtonFactory::setSize(const sf::Vector2f& size) {
    this->size = size;
    return *this;
}


ButtonFactory& ButtonFactory::setText(const std::string& text) {
    this->text = text;
    return *this;
}


ButtonFactory& ButtonFactory::setOnClickId(GlobalId onClickId) {
    this->onClickId = onClickId;
    return *this;
}


ButtonFactory& ButtonFactory::setOnClick(const std::function<void(Message&)> onClick) {
    this->onClick = onClick;
    return *this;
}

ButtonFactory& ButtonFactory::setDrawn(const bool drawn) {
    this->drawn = drawn;
    return *this;
}


TIEntity& ButtonFactory::build() {
	TIEntity& uiElement = this->UIElementFactory::build();

    PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(uiElement);
    positionComponent.position = this->position;

    ShapeComponent& shapeComponent = ShapeComponentSystem::Instance()->addComponent(uiElement);
    sf::RectangleShape& rectangleShape = shapeComponent.addRectangleShape();
    rectangleShape.setSize(this->size);
    rectangleShape.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
    rectangleShape.setOutlineThickness(2);
    rectangleShape.setOutlineColor(sf::Color::White);
    rectangleShape.setFillColor(sf::Color::Transparent);
    shapeComponent.setDrawn(this->drawn);

    TextComponent& textComponent = TextComponentSystem::Instance()->addComponent(uiElement);
    textComponent.setTextAlignment(TextAlignment::CENTER);
    textComponent.setString(this->text);
    textComponent.setCharacterSize(16);
    textComponent.setDrawn(this->drawn);

    if (this->onClickId) {
        ClickableComponentSystem::Instance()->setOnClick(uiElement, this->onClickId);
    } else if (this->onClick) {
        ClickableComponentSystem::Instance()->setOnClick(uiElement, this->onClick);
    }

	return uiElement;
}
