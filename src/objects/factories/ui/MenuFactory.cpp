#include "objects/factories/ui/MenuFactory.h"

#include "componentsystems/EventsComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"
#include "constants/MessageSubscriptions.h"
#include "managers/MessageManager.h"
#include "objects/ScriptTableReader.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "objects/factories/ui/UIElementFactory.h"
#include "objects/tientities/ui/Menu.h"

using namespace TIE;

MenuFactory::MenuFactory(): TIEntityFactory() {}


MenuFactory::MenuFactory(const sol::table& definition): TIEntityFactory(definition) {}


MenuFactory& MenuFactory::setPosition(const sf::Vector2f& position) {
    this->position = position;
    return *this;
}


MenuFactory& MenuFactory::setOnClick(const std::function<void(Message&)> onClick) {
    this->onClick = onClick;
    return *this;
}

MenuFactory& MenuFactory::setDrawn(const bool drawn) {
    this->drawn = drawn;
    return *this;
}


TIEntity& MenuFactory::build() {
    return this->build(this->getReader());
}

TIEntity& MenuFactory::build(const ScriptTableReader& reader) {
    Menu* menu = static_cast<Menu*>(&this->TIEntityFactory::build(reader));

    PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(*menu);
    positionComponent.position = this->position;

    const GlobalId subscriptionId = MessageManager::Instance()->getSubscriptionId(MessageSubscriptions::MOUSE_BUTTON_PRESSED);
    EventsComponentSystem::Instance()->subscribe(*menu, subscriptionId, std::bind(&Menu::onClick, menu, std::placeholders::_1));

    for (auto& buttonReader : reader.getReader(MenuFactory::BUTTONS).getReaders()) {
        UIElementFactory uiElementFactory = UIElementFactory();
        uiElementFactory.setParent(menu);
        TIEntity& button = UIElementFactory().build(buttonReader.second);
    }

	return *menu;
}
