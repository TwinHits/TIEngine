#include "componentsystems/TextComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/ShapeComponentSystem.h"
#include "managers/AssetsManager.h"
#include "objects/assets/FontAsset.h"
#include "objects/components/TextComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/tientities/TIEntity.h"
#include "objects/enumeration/TextAlignment.h"
#include "objects/factories/TIEntityFactory.h"
#include "utils/ComponentSystems.h"
#include "utils/StringHelpers.h"

using namespace TIE;

TextComponentSystem::TextComponentSystem() {
	ComponentSystems::insertComponentPropertyIntoMap(TextComponentSystem::DRAWN, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(TextComponentSystem::STRING, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(TextComponentSystem::FONT, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(TextComponentSystem::OFFSET_X, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(TextComponentSystem::OFFSET_Y, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(TextComponentSystem::TEXT_ALIGNMENT, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(TextComponentSystem::CHARACTER_SIZE, this->componentPropertyMap);
}


void TextComponentSystem::update(const float delta) {
	for (auto& c : this->components) {	
		c.textComponent.setPosition(c.positionComponent.worldPosition);
		c.textComponent.setRotation(c.positionComponent.worldRotation);
	}
}


bool TextComponentSystem::hasComponent(const TIEntity& tientity) {
	return tientity.hasComponent<TextComponent>();
}


TextComponent& TextComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<TextComponent>()) {
		TextComponent& textComponent = tientity.addComponent<TextComponent>();
		PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);
		this->components.push_back({ textComponent, positionComponent, tientity });
		return textComponent;
	} else {
		return *tientity.getComponent<TextComponent>();
	}
}


TextComponent& TextComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
    TextComponent& textComponent = this->addComponent(tientity);

	bool drawn = ComponentSystems::getFactoryValue<bool>(factory, TextComponentSystem::DRAWN, textComponent.isDrawn(), tientity);
    textComponent.setDrawn(drawn);

	const std::string& text = ComponentSystems::getFactoryValue<std::string>(factory, TextComponentSystem::STRING, textComponent.getText().getString(), tientity);
    textComponent.setString(text);

	const std::string& fontName = ComponentSystems::getFactoryValue<std::string>(factory, TextComponentSystem::FONT, TextComponentSystem::FONT_DEFAULT, tientity);
	const FontAsset& font = AssetsManager::Instance()->getFont(fontName);
	textComponent.setFont(font);

	float characterSize = ComponentSystems::getFactoryValue<float>(factory, TextComponentSystem::CHARACTER_SIZE, textComponent.getCharacterSize(), tientity);
    textComponent.setCharacterSize(characterSize);

	TextAlignment textAlignment = TIE::String::strToTextAlignment(ComponentSystems::getFactoryValue<std::string>(factory, TextComponentSystem::TEXT_ALIGNMENT, TIE::String::textAlignmentToStr(textComponent.getTextAlignment()), tientity));
	textComponent.setTextAlignment(textAlignment);

	bool showWireframe = ComponentSystems::getFactoryValue<bool>(factory, TextComponentSystem::SHOW_WIREFRAME, TextComponentSystem::SHOW_WIREFRAME_DEFAULT, tientity);
	if (showWireframe) {
		ShapeComponentSystem::Instance()->addWireframe(tientity, textComponent);
	}

	return textComponent;
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
	TextComponent* component = tientity.getComponent<TextComponent>();
	if (component != nullptr) {
		if (key == TextComponentSystem::STRING) {
			component->setString(std::to_string(value));
		} else if (key == TextComponentSystem::DRAWN) {
			component->setDrawn(value);
		}
	}
	return false;
}


bool TextComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity)  {
	TextComponent* component = tientity.getComponent<TextComponent>();
	if (component != nullptr) {
		if (key == TextComponentSystem::STRING) {
			component->setString(std::to_string(value));
		} else if (key == TextComponentSystem::CHARACTER_SIZE) {
			component->setCharacterSize(value);
		}
	}
	return false;
}


bool TextComponentSystem::setComponentProperty(const std::string& key, const std::string& value, TIEntity& tientity) {
	TextComponent* component = tientity.getComponent<TextComponent>();
	if (component != nullptr) {
		if (key == TextComponentSystem::STRING) {
			component->setString(value);
		} else if (key == TextComponentSystem::TEXT_ALIGNMENT) {
			component->setTextAlignment(TIE::String::strToTextAlignment(value));
		} else if (key == TextComponentSystem::FONT) {
			component->setFont(AssetsManager::Instance()->getFont(value));
		}
	}
    return false;
}


sol::object TextComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
	TextComponent* component = tientity.getComponent<TextComponent>();
	if (component != nullptr) {
		if (key == TextComponentSystem::STRING) {
			return ScriptManager::Instance()->getObjectFromValue(std::string(component->getString()));
		} else if (key == TextComponentSystem::CHARACTER_SIZE) {
			return ScriptManager::Instance()->getObjectFromValue(component->getCharacterSize());
		} else if (key == TextComponentSystem::TEXT_ALIGNMENT) {
			return ScriptManager::Instance()->getObjectFromValue(TIE::String::textAlignmentToStr(component->getTextAlignment()));
		} else if (key == TextComponentSystem::FONT) {
			return ScriptManager::Instance()->getObjectFromValue(component->getFont().getName());
		}
	}
	return ScriptManager::Instance()->getObjectFromValue(nullptr);
}


void TextComponentSystem::setOriginForTextAlignment(TextComponent& textComponent) {
	TextAlignment textAlignment = textComponent.getTextAlignment();
	sf::FloatRect bounds = textComponent.getLocalBounds();

	if (textAlignment == TextAlignment::TOP_LEFT) {
		textComponent.setOrigin(0,0);
	} else if (textAlignment == TextAlignment::TOP_CENTER) {
		textComponent.setOrigin(bounds.left + bounds.width / 2, 0);
	} else if (textAlignment == TextAlignment::TOP_RIGHT) {
		textComponent.setOrigin(bounds.left + bounds.width, 0);
	} else if (textAlignment == TextAlignment::CENTER_LEFT) {
		textComponent.setOrigin(0, bounds.top + bounds.height / 2);
	} else if (textAlignment == TextAlignment::CENTER) {
		textComponent.setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
	} else if (textAlignment == TextAlignment::CENTER_RIGHT) {
		textComponent.setOrigin(bounds.left + bounds.width, bounds.top + bounds.height / 2);
	} else if (textAlignment == TextAlignment::BOTTOM_LEFT) {
		textComponent.setOrigin(0, bounds.top + bounds.height);
	} else if (textAlignment == TextAlignment::BOTTOM_CENTER) {
		textComponent.setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height);
	} else if (textAlignment == TextAlignment::BOTTOM_RIGHT) {
		textComponent.setOrigin(bounds.left + bounds.width, bounds.top + bounds.height);
	}
}
