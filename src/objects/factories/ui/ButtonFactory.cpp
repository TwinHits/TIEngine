#include "objects/factories/ui/ButtonFactory.h"

#include "componentsystems/ClickableComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/ShapeComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"
#include "objects/ScriptTableReader.h"
#include "objects/factories/tientities/TIEntityFactory.h"

using namespace TIE;

ButtonFactory::ButtonFactory(): TIEntityFactory() {}


ButtonFactory::ButtonFactory(const sol::table& definition): TIEntityFactory(definition) {
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
    return this->build(this->getReader());
}


TIEntity& ButtonFactory::build(const ScriptTableReader& reader) {
	TIEntity& button = this->TIEntityFactory::build(reader);

    this->text = reader.get<std::string>(ButtonFactory::TEXT, this->text);
    this->onClickId = reader.get<GlobalId>(ButtonFactory::ON_CLICK, this->onClickId);

    PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(button);
    positionComponent.position = this->position;

    ShapeComponent& shapeComponent = ShapeComponentSystem::Instance()->addComponent(button);
    sf::RectangleShape& rectangleShape = shapeComponent.addRectangleShape();
    rectangleShape.setSize(this->size);
    rectangleShape.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
    rectangleShape.setOutlineThickness(2);
    rectangleShape.setOutlineColor(sf::Color::White);
    rectangleShape.setFillColor(sf::Color::Transparent);
    shapeComponent.setDrawn(this->drawn);

    TextComponent& textComponent = TextComponentSystem::Instance()->addComponent(button);
    textComponent.setTextAlignment(TextAlignment::CENTER);
    textComponent.setString(this->text);
    textComponent.setCharacterSize(16);
    textComponent.setDrawn(this->drawn);

    if (this->onClickId) {
        ClickableComponentSystem::Instance()->setOnClick(button, this->onClickId);
    } else if (this->onClick) {
        ClickableComponentSystem::Instance()->setOnClick(button, this->onClick);
    }

	return button;
}
