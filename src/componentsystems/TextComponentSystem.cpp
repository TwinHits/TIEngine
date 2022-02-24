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

	std::string text = ComponentSystems::getFactoryValue<std::string>(factory, TextComponentSystem::CONTENT, "", tientity);
	bool drawn = ComponentSystems::getFactoryValue<bool>(factory, TextComponentSystem::DRAWN, false, tientity);

    textComponent.setString(text);
    textComponent.setDrawn(drawn);
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
