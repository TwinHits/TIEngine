#include "utils/ComponentSystems.h"

#include "objects/components/SpriteComponent.h"
#include "objects/components/TextComponent.h"
#include "objects/components/ShapeComponent.h"
#include "objects/components/SpriteComponent.h"
#include "utils/StringHelpers.h"

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

void ComponentSystems::setDrawn(TIEntity& entity, bool drawn) {
    SpriteComponent* spriteComponent = entity.getComponent<SpriteComponent>();
    TextComponent* textComponent = entity.getComponent<TextComponent>();
    ShapeComponent* shapeComponent = entity.getComponent<ShapeComponent>();
    
    if (spriteComponent != nullptr) {
        spriteComponent->setDrawn(drawn);
    }

    if (textComponent != nullptr) {
        textComponent->setDrawn(drawn);
    }

    if (shapeComponent != nullptr) {
        shapeComponent->setDrawn(drawn);
    }
}

bool ComponentSystems::isDrawn(TIEntity& entity) {
    SpriteComponent* spriteComponent = entity.getComponent<SpriteComponent>();
    TextComponent* textComponent = entity.getComponent<TextComponent>();
    ShapeComponent* shapeComponent = entity.getComponent<ShapeComponent>();
    
    bool isDrawn = false;
    if (spriteComponent != nullptr && !isDrawn) {
        isDrawn = spriteComponent->isDrawn();
    }

    if (textComponent != nullptr && !isDrawn) {
        isDrawn = textComponent->isDrawn();
    }

    if (shapeComponent != nullptr && !isDrawn) {
        isDrawn = shapeComponent->isDrawn();
    }

    return isDrawn;
}


std::string ComponentSystems::getComponentNameFromKey(const std::string& key) {
    std::vector<std::string> parts;
    String::split(key, '.', parts);
    return parts.front();
}
