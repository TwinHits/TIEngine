#include "objects/factories/ui/UIElementFactory.h"

#include "objects/ScriptTableReader.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

UIElementFactory::UIElementFactory() : TIEntityFactory() {}


UIElementFactory::UIElementFactory(const sol::table& definition) : TIEntityFactory(definition) {}


UIElementFactory::UIElementFactory(const ScriptTableReader& reader) : TIEntityFactory(reader) {}


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
    const std::string name = this->getReader().get<std::string>(TIEntityFactory::NAME, "");

    this->setName(name);

    TIEntity& uiElement = TIEntityFactory::build();

    return uiElement;
}
