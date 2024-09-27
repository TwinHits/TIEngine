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


UIElementFactory& UIElementFactory::setText(const std::string& text) {
    this->text = text;
    return *this;
}


const std::string& UIElementFactory::getText() {
    return this->text;
}


UIElementFactory& UIElementFactory::setOnEventId(const GlobalId onEventId) {
    this->onEventId = onEventId;
    return *this;
}


const GlobalId UIElementFactory::getOnEventId() {
    return this->onEventId;
}


TIEntity& UIElementFactory::build() {
    this->setName(this->getReader().get<std::string>(TIEntityFactory::NAME, this->getName()));
    this->drawn = this->getReader().get<bool>(UIElementFactory::DRAWN, this->drawn);
    this->text = this->getReader().get<std::string>(UIElementFactory::TEXT, this->text);
    this->position = sf::Vector2f(
        this->getReader().get<float>(UIElementFactory::POSITION_X, this->position.x),
        this->getReader().get<float>(UIElementFactory::POSITION_Y, this->position.y)
    );
    this->onEventId = (this->getReader().get<GlobalId>(UIElementFactory::ON_EVENT_ID, this->onEventId));

    return TIEntityFactory::build();
}
