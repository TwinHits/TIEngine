#include "componentsystems/TextComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "componentsystems/PositionComponentSystem.h"
#include "objects/components/TextComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "utils/ComponentSystems.h"

using namespace TIE;

void TextComponentSystem::update(const float delta) {
	for (auto& c : this->components) {	
		c.textComponent.setPosition(c.positionComponent.worldPosition);
		c.textComponent.setRotation(c.positionComponent.worldRotation);
	}
}


void TextComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
    TextComponent& textComponent = tientity.addComponent<TextComponent>();
    PositionComponent& positionComponent = tientity.addComponent<PositionComponent>();
    Components components = { textComponent, positionComponent, tientity };
    this->components.push_back(components);

	std::string text = ComponentSystems::getFactoryValue<std::string>(factory, TextComponentSystem::CONTENT, textComponent.getText().getString(), tientity);
	bool drawn = ComponentSystems::getFactoryValue<bool>(factory, TextComponentSystem::DRAWN, textComponent.isDrawn(), tientity);

    textComponent.setString(text);
    textComponent.setDrawn(drawn);

	textComponent.setOrigin(textComponent.getLocalBounds().width / 2, textComponent.getLocalBounds().height / 2);
}


bool TextComponentSystem::removeComponent(TIEntity& tientity) {
	TextComponent* textComponent = tientity.getComponent<TextComponent>();
	if (textComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->textComponent == textComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<TextComponent>();
	} else {
		return false;
	}
}


const std::string& TextComponentSystem::getName() {
	return TextComponentSystem::TEXT;
}


bool TextComponentSystem::setComponentProperty(const std::string& key, bool value, TIEntity& tientity) {
    return false;
}


bool TextComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity)  {
    return false;
}


bool TextComponentSystem::setComponentProperty(const std::string& key, const std::string& value, TIEntity& tientity)  {
    return false;
}


sol::object TextComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
	return ScriptManager::Instance()->getObjectFromValue(nullptr);
}


ComponentSystems::ComponentSystemPropertiesMap& TextComponentSystem::populateComponentSystemsPropertiesMap(ComponentSystems::ComponentSystemPropertiesMap& map) {
	ComponentSystems::insertComponentPropertyIntoMap(TextComponentSystem::DRAWN, map);
	ComponentSystems::insertComponentPropertyIntoMap(TextComponentSystem::CONTENT, map);
	ComponentSystems::insertComponentPropertyIntoMap(TextComponentSystem::OFFSET_X, map);
	ComponentSystems::insertComponentPropertyIntoMap(TextComponentSystem::OFFSET_Y, map);
	return map;
}
