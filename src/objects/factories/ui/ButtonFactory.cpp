#include "objects/factories/ui/ButtonFactory.h"

#include "componentsystems/ClickableComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/ShapeComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"

using namespace TIE;

ButtonFactory::ButtonFactory(): UIElementFactory() {}


ButtonFactory::ButtonFactory(const sol::table& definition): UIElementFactory(definition) {}


ButtonFactory::ButtonFactory(const ScriptTableReader& reader): UIElementFactory(reader) {}


ButtonFactory& ButtonFactory::setOnClickId(GlobalId onClickId) {
    this->onClickId = onClickId;
    return *this;
}


ButtonFactory& ButtonFactory::setOnClick(const std::function<void(Message&)> onClick) {
    this->onClick = onClick;
    return *this;
}


TIEntity& ButtonFactory::build() {
	TIEntity& button = this->UIElementFactory::build();

    this->onClickId = this->getReader().get<GlobalId>(ButtonFactory::ON_CLICK, this->onClickId);

    PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(button);
    positionComponent.position = this->getPosition();

    ShapeComponent& shapeComponent = ShapeComponentSystem::Instance()->addComponent(button);
    sf::RectangleShape& rectangleShape = shapeComponent.addRectangleShape();
    rectangleShape.setSize(this->getSize());
    rectangleShape.setOrigin(sf::Vector2f(this->getSize().x / 2, this->getSize().y / 2));
    rectangleShape.setOutlineThickness(2);
    rectangleShape.setOutlineColor(sf::Color::White);
    rectangleShape.setFillColor(sf::Color::Transparent);
    shapeComponent.setDrawn(this->getDrawn());

    TextComponent& textComponent = TextComponentSystem::Instance()->addComponent(button);
    textComponent.setTextAlignment(TextAlignment::CENTER);
    textComponent.setString(this->getText());
    textComponent.setCharacterSize(16);
    textComponent.setDrawn(this->getDrawn());

    if (this->onClickId) {
        ClickableComponentSystem::Instance()->setOnClick(button, this->onClickId);
    } else if (this->onClick) {
        ClickableComponentSystem::Instance()->setOnClick(button, this->onClick);
    }

	return button;
}
