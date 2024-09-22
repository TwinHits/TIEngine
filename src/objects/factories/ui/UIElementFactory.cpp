#include "objects/factories/ui/UIElementFactory.h"

#include "managers/HashManager.h"
#include "objects/ScriptTableReader.h"
#include "objects/factories/ui/ButtonFactory.h"
#include "objects/factories/ui/MenuFactory.h"
#include "templates/MakeUnique.h"

using namespace TIE;

UIElementFactory::UIElementFactory() : TIEntityFactory() {}


UIElementFactory::UIElementFactory(const sol::table& definition) : TIEntityFactory(definition) {}


UIElementFactory& UIElementFactory::setDrawn(const bool drawn) {
    this->drawn = drawn;
    return *this;
}

const bool UIElementFactory::getDrawn() {
    return this->drawn;
}


UIElementFactory& UIElementFactory::setPosition(const sf::Vector2f& position) {
    this->position = position;
    return *this;
}


const sf::Vector2f& UIElementFactory::getPosition() {
    return this->position;
}


UIElementFactory& UIElementFactory::setSize(const sf::Vector2f& size) {
    this->size = size;
    return *this;
}


const sf::Vector2f& UIElementFactory::getSize() {
    return this->size;
}


TIEntity& UIElementFactory::build() {
    return this->build(this->getReader());
}


TIEntity& UIElementFactory::build(const ScriptTableReader& reader) {
    const std::string type = reader.get<std::string>(UIElementFactory::TYPE, "");
    const std::string name = reader.get<std::string>(TIEntityFactory::NAME, "");

    std::unique_ptr<UIElementFactory> uiElementFactory = nullptr;
    if (type == UIElementFactory::MENU) {
        uiElementFactory = TIE::make_unique<MenuFactory>();
    } else if (type == UIElementFactory::BUTTON) {
        uiElementFactory = TIE::make_unique<ButtonFactory>();
    } else {
        return this->TIEntityFactory::build();
    }

    uiElementFactory->setParent(this->getParent());
    uiElementFactory->setName(name);
    uiElementFactory->setPosition(this->position);
    uiElementFactory->setSize(this->size);
    uiElementFactory->setDrawn(this->drawn);
    
    return uiElementFactory->build(reader);
}
