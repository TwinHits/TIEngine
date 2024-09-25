#include "objects/factories/ui/MenuFactory.h"

#include "componentsystems/EventsComponentSystem.h"
#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"
#include "constants/MessageSubscriptions.h"
#include "managers/AssetsManager.h"
#include "managers/MessageManager.h"
#include "objects/ScriptTableReader.h"
#include "objects/builders/UIElementFactoryBuilder.h"
#include "objects/factories/ui/UIElementFactory.h"
#include "objects/tientities/TIEntity.h"
#include "objects/tientities/ui/Menu.h"

using namespace TIE;

MenuFactory::MenuFactory(): UIElementFactory() {}


MenuFactory::MenuFactory(const sol::table& definition): UIElementFactory(definition) {}


MenuFactory::MenuFactory(const ScriptTableReader& reader): UIElementFactory(reader) {}


MenuFactory& MenuFactory::setPosition(const sf::Vector2f& position) {
    this->position = position;
    return *this;
}


MenuFactory& MenuFactory::setEvent(const std::string& event) {
    this->event = event;
    return *this;
}


TIEntity& MenuFactory::build() {
    Menu* menu = static_cast<Menu*>(&this->UIElementFactory::build());

    PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(*menu);
    positionComponent.position = this->position;

	const FontAsset& font = AssetsManager::Instance()->getFont(ConfigManager::Instance()->getEngineFontName());
    TextComponentSystem::Instance()->addComponent(*menu, font, this->getName(), 16, TextAlignment::BOTTOM_LEFT, this->getDrawn());

    const GlobalId subscriptionId = MessageManager::Instance()->getSubscriptionId(this->event);
    EventsComponentSystem::Instance()->subscribe(*menu, subscriptionId, std::bind(&Menu::onClick, menu, std::placeholders::_1));

    sf::Vector2f buttonSize = sf::Vector2f(100, 25);
    sf::Vector2f position = sf::Vector2f(buttonSize.x / 2 ,buttonSize.y / 2);
    for (auto& [key, menuItemReader] : this->getReader().getReader(MenuFactory::MENU_ITEMS).getReaders()) {
        std::unique_ptr<UIElementFactory> uiElementFactory = UIElementFactoryBuilder::make_factory(menuItemReader, menu);
        uiElementFactory->setParent(menu);
        uiElementFactory->setDrawn(true);
        uiElementFactory->setSize(buttonSize);
        uiElementFactory->setPosition(position);
        TIEntity& uiElement = uiElementFactory->build();
        position.y = position.y + uiElementFactory->getSize().y;
    }

	return *menu;
}
