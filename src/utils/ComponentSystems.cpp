#include "utils/ComponentSystems.h"

#include "objects/components/SpriteComponent.h"
#include "objects/components/TextComponent.h"
#include "objects/components/ShapeComponent.h"
#include "objects/components/SpriteComponent.h"
#include "utils/StringHelpers.h"
#include "utils/types/ComponentSystemsTypes.h"

using namespace TIE;

template <>
bool ComponentSystems::getFactoryValue<bool>(const TIEntityFactory& factory, const std::string& key, bool defaultReturn, TIEntity& tientity) {
    if (factory.boolValues.count(key)) {
        return factory.boolValues.at(key);
    } else if (factory.functionValues.count(key)) {
        return ScriptManager::Instance()->runFunction<bool>(factory.functionValues.at(key), tientity);
    } else {
        return defaultReturn;
    }
}


template <>
float ComponentSystems::getFactoryValue<float>(const TIEntityFactory& factory, const std::string& key, float defaultReturn, TIEntity& tientity) {
    if (factory.floatValues.count(key)) {
        return factory.floatValues.at(key);
    } else if (factory.functionValues.count(key)) {
        return ScriptManager::Instance()->runFunction<float>(factory.functionValues.at(key), tientity);
    } else {
        return defaultReturn;
    }
}


template <>
std::string ComponentSystems::getFactoryValue<std::string>(const TIEntityFactory& factory, const std::string& key, std::string defaultReturn, TIEntity& tientity) {
    if (factory.stringValues.count(key)) {
        return factory.stringValues.at(key);
    } else if (factory.functionValues.count(key)) {
        return ScriptManager::Instance()->runFunction<std::string>(factory.functionValues.at(key), tientity);
    } else {
        return defaultReturn;
    }
}


std::string ComponentSystems::getComponentNameFromKey(const std::string& key) {
    std::vector<std::string> parts;
    String::split(key, '.', parts);
    return parts.front();
}


ComponentSystems::ComponentSystemPropertiesMap& ComponentSystems::insertComponentPropertyIntoMap(const std::string& property, ComponentSystemPropertiesMap& map) {
    std::vector<std::string> parts;
    String::split(property, '.', parts);

	if (!map.count(parts.front())) {
		map[parts.front()];
	}
	map[parts.front()][parts.back()] = property;

	return map;
}


void ComponentSystems::setDrawn(TIEntity& entity, const bool drawn) {

	TextComponent* textComponent = entity.getComponent<TextComponent>();
	SpriteComponent* spriteComponent = entity.getComponent<SpriteComponent>();
	ShapeComponent* shapeComponent = entity.getComponent<ShapeComponent>();

	if (textComponent != nullptr) {
		textComponent->setDrawn(drawn);
	}

	if (spriteComponent != nullptr) {
		spriteComponent->setDrawn(drawn);
	}

	if (shapeComponent != nullptr) {
		shapeComponent->setDrawn(drawn);
	}
}


bool ComponentSystems::isDrawn(TIEntity& entity) {

	TextComponent* textComponent = entity.getComponent<TextComponent>();
	SpriteComponent* spriteComponent = entity.getComponent<SpriteComponent>();
	ShapeComponent* shapeComponent = entity.getComponent<ShapeComponent>();

	if (textComponent != nullptr && textComponent->isDrawn()) {
		return textComponent->isDrawn();
	}

	if (spriteComponent != nullptr && spriteComponent->isDrawn()) {
		return spriteComponent->isDrawn();
	}

	if (shapeComponent != nullptr && shapeComponent->isDrawn()) {
		return shapeComponent->isDrawn();
	}

	return false;
}


const sf::FloatRect ComponentSystems::getGlobalBounds(TIEntity& tientity) {

	ShapeComponent* shapeComponent = tientity.getComponent<ShapeComponent>();
	if (shapeComponent != nullptr && shapeComponent->isDrawn()) {
		for (auto& shape : shapeComponent->getShapes()) {
			return shape->getGlobalBounds();
		}
	}

	SpriteComponent* spriteComponent = tientity.getComponent<SpriteComponent>();
	if (spriteComponent != nullptr && spriteComponent->isDrawn()) {
		return spriteComponent->getGlobalBounds();
	}

	TextComponent* textComponent = tientity.getComponent<TextComponent>();
	if (textComponent != nullptr && textComponent->isDrawn()) {
		return textComponent->getGlobalBounds();
	}

	return sf::FloatRect(-1, 0, 0, 0);
}


const sf::FloatRect ComponentSystems::getLocalBounds(TIEntity& tientity) {

	ShapeComponent* shapeComponent = tientity.getComponent<ShapeComponent>();
	if (shapeComponent != nullptr && shapeComponent->isDrawn()) {
		for (auto& shape : shapeComponent->getShapes()) {
			return shape->getLocalBounds();
		}
	}

	SpriteComponent* spriteComponent = tientity.getComponent<SpriteComponent>();
	if (spriteComponent != nullptr && spriteComponent->isDrawn()) {
		return spriteComponent->getLocalBounds();
	}

	TextComponent* textComponent = tientity.getComponent<TextComponent>();
	if (textComponent != nullptr && textComponent->isDrawn()) {
		return textComponent->getLocalBounds();
	}

	return sf::FloatRect(-1, 0, 0, 0);
}
