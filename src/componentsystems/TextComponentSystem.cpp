#include "componentsystems/TextComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "enumeration/TextAlignment.h"
#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/WireframeComponentSystem.h"
#include "managers/AssetsManager.h"
#include "managers/ComponentSystemsManager.h"
#include "objects/assets/FontAsset.h"
#include "objects/components/TextComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/tientities/TIEntity.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "utils/ComponentSystems.h"
#include "utils/String.h"

using namespace TIE;

TextComponentSystem::TextComponentSystem() {
	this->setName(TextComponentSystem::TEXT);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(TextComponentSystem::DRAWN, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(TextComponentSystem::STRING, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(TextComponentSystem::FONT, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(TextComponentSystem::OFFSET_X, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(TextComponentSystem::OFFSET_Y, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(TextComponentSystem::TEXT_ALIGNMENT, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(TextComponentSystem::CHARACTER_SIZE, this);
}


void TextComponentSystem::update(const float delta) {
	for (auto& c : this->components) {	
		c.textComponent.setPosition(c.positionComponent.worldPosition);
		c.textComponent.setRotation(c.positionComponent.worldRotation);
	}
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
	const ScriptTableReader& reader = factory.getReader().getReader(TextComponentSystem::TEXT);

	const bool& drawn = reader.get<bool>(TextComponentSystem::DRAWN, textComponent.isDrawn());
    textComponent.setDrawn(drawn);

	const std::string& text = reader.get<std::string>(TextComponentSystem::STRING, textComponent.getText().getString());
    textComponent.setString(text);

	const std::string& fontName = reader.get<std::string>(TextComponentSystem::FONT, TextComponentSystem::FONT_DEFAULT);
	const FontAsset& font = AssetsManager::Instance()->getFont(fontName);
	textComponent.setFont(font);

	const float& characterSize = reader.get<float>(TextComponentSystem::CHARACTER_SIZE, textComponent.getCharacterSize());
    textComponent.setCharacterSize(characterSize);

	TextAlignment textAlignment = TIE::String::strToTextAlignment(reader.get<std::string>(TextComponentSystem::TEXT_ALIGNMENT, TIE::String::textAlignmentToStr(textComponent.getTextAlignment())));
	textComponent.setTextAlignment(textAlignment);

	return textComponent;
}

TextComponent& TextComponentSystem::addComponent(TIEntity& tientity, const FontAsset& font, const std::string& text, const int fontSize, const TextAlignment textAlignment, const bool drawn) {
	TextComponent& textComponent = this->addComponent(tientity);
	textComponent.setFont(font);
	textComponent.setString(text);
	textComponent.setCharacterSize(fontSize);
	textComponent.setTextAlignment(textAlignment);
	textComponent.setDrawn(true);
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


void TextComponentSystem::setComponentProperty(const std::string& key, bool value, TIEntity& tientity) {
	TextComponent& component = this->addComponent(tientity);
    if (key == TextComponentSystem::STRING) {
        component.setString(std::to_string(value));
    } else if (key == TextComponentSystem::DRAWN) {
        component.setDrawn(value);
    }
}


void TextComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity)  {
	TextComponent& component = this->addComponent(tientity);
    if (key == TextComponentSystem::STRING) {
        component.setString(std::to_string(value));
    } else if (key == TextComponentSystem::CHARACTER_SIZE) {
        component.setCharacterSize(value);
    }
}


void TextComponentSystem::setComponentProperty(const std::string& key, const std::string& value, TIEntity& tientity) {
	TextComponent& component = this->addComponent(tientity);
    if (key == TextComponentSystem::STRING) {
        component.setString(value);
    } else if (key == TextComponentSystem::TEXT_ALIGNMENT) {
        component.setTextAlignment(TIE::String::strToTextAlignment(value));
    } else if (key == TextComponentSystem::FONT) {
        component.setFont(AssetsManager::Instance()->getFont(value));
    }
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


std::pair<GlobalId, GlobalId> TextComponentSystem::addWireframe(TIEntity& tientity) {
	TextComponent* textComponent = tientity.getComponent<TextComponent>();
	if (textComponent) {
		return WireframeComponentSystem::Instance()->createWireframe(tientity, textComponent->getGlobalBounds(), textComponent->getOrigin());
	} 
	return std::pair(0,0);
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
