#include "objects/builders/UIElementFactoryBuilder.h"

#include <memory>

#include "sol/sol.hpp"

#include "managers/LogManager.h"
#include "objects/ScriptTableReader.h"
#include "objects/factories/ui/ButtonFactory.h"
#include "objects/factories/ui/LabelFactory.h"
#include "objects/factories/ui/MenuFactory.h"

using namespace TIE;

// TODO Technically this is a Factory and the Factorys are Builders
std::unique_ptr<UIElementFactory> UIElementFactoryBuilder::make_factory(const ScriptTableReader& reader) {
    const std::string& type = reader.get<std::string>(UIElementFactoryBuilder::TYPE, "");
    std::unique_ptr<UIElementFactory> uiElementFactory = nullptr;
    if (type == UIElementFactoryBuilder::MENU) {
        uiElementFactory = std::make_unique<MenuFactory>(reader);
    } else if (type == UIElementFactoryBuilder::BUTTON) {
        uiElementFactory = std::make_unique<ButtonFactory>(reader);
    } else if (type == UIElementFactoryBuilder::LABEL) {
        uiElementFactory = std::make_unique<LabelFactory>(reader);
    } else {
        LogManager::Instance()->error("Attempted to build UIElement with an unknown type " + type);
        uiElementFactory = std::make_unique<UIElementFactory>(reader);
    }

    return uiElementFactory;
}


std::unique_ptr<UIElementFactory> UIElementFactoryBuilder::make_factory(const sol::table& definition) {
    const std::string& type = definition.get_or<std::string>(UIElementFactoryBuilder::TYPE, "");
    std::unique_ptr<UIElementFactory> uiElementFactory = nullptr;
    if (type == UIElementFactoryBuilder::MENU) {
        uiElementFactory = std::make_unique<MenuFactory>(definition);
    } else if (type == UIElementFactoryBuilder::BUTTON) {
        uiElementFactory = std::make_unique<ButtonFactory>(definition);
    } else if (type == UIElementFactoryBuilder::LABEL) {
        uiElementFactory = std::make_unique<LabelFactory>(definition);
    } else {
        LogManager::Instance()->error("Attempted to build UIElement with an unknown type " + type);
        uiElementFactory = std::make_unique<UIElementFactory>(definition);
    }

    return uiElementFactory;
}
