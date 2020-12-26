#include "interfaces/TIEngineInterface.h"

#include <string>

#include <sol/sol.hpp>

#include "interfaces/TIEntityInterface.h"
#include "interfaces/Vector2Interface.h"
#include "managers/AssetsManager.h"
#include "managers/EventsManager.h"
#include "managers/LogManager.h"
#include "managers/ScriptManager.h"
#include "managers/WindowManager.h"
#include "managers/WorldManager.h"
#include "utils/StringHelpers.h"

using namespace TIE;

void TIEngineInterface::registerUserType(sol::state& luaState) {
	sol::usertype<TIEngineInterface> engineInterfaceUserType = luaState.new_usertype<TIEngineInterface>("tiengine");
    engineInterfaceUserType["isValid"] = &TIEngineInterface::isValid;
    engineInterfaceUserType["registerTexturesDirectory"] = &TIEngineInterface::registerTexturesDirectory;
    engineInterfaceUserType["registerFontDirectory"] = &TIEngineInterface::registerFontsDirectory;
    engineInterfaceUserType["registerAudioDirectory"] = &TIEngineInterface::registerAudioDirectory;
    engineInterfaceUserType["setWindowTitle"] = &TIEngineInterface::setWindowTitle;
    engineInterfaceUserType["setWindowSize"] = &TIEngineInterface::setWindowSize;
    engineInterfaceUserType["registerLevel"] = &TIEngineInterface::registerLevel;
    engineInterfaceUserType["setLevel"] = &TIEngineInterface::setLevel;
	engineInterfaceUserType["registerTIEntity"] = &TIEngineInterface::registerTIEntityDefinition;
	engineInterfaceUserType["spawn"] = &TIEngineInterface::spawnTIEntity;
	engineInterfaceUserType["hasEvent"] = &TIEngineInterface::hasEvent;
	engineInterfaceUserType["getMouseClickPosition"] = &TIEngineInterface::getMouseClickPosition;
    engineInterfaceUserType["getTIEntityById"] = &TIEngineInterface::getTIEntityById;
    engineInterfaceUserType["registerBehavior"] = &TIEngineInterface::registerBehavior;
}


bool TIEngineInterface::isValid() {
    return this != nullptr;
}


bool TIEngineInterface::registerTexturesDirectory(const std::string& directory) {
    return AssetsManager::Instance()->loadTexturesFromPath(ScriptManager::Instance()->getScriptWorkingDirectory() + directory);
}


bool TIEngineInterface::registerFontsDirectory(const std::string& directory) {
    return AssetsManager::Instance()->loadFontsFromPath(ScriptManager::Instance()->getScriptWorkingDirectory() + directory);
}


bool TIEngineInterface::registerAudioDirectory(const std::string& directory) {
    return AssetsManager::Instance()->loadAudioFromPath(ScriptManager::Instance()->getScriptWorkingDirectory() + directory);
}


bool TIEngineInterface::setWindowSize(const int width, const int height) {
	WindowManager::Instance()->updateWindowSize(width, height);
    return true;
}


bool TIEngineInterface::setWindowTitle(const std::string& title) {
	WindowManager::Instance()->setTitle(title);
    return true;
}


bool TIEngineInterface::registerLevel(const std::string& name, const sol::table& definition) {
    ScriptManager::Instance()->loadTIEntityDefinition(name, definition);
    return true;
}


bool TIEngineInterface::setLevel(const std::string& name) {
    if (WorldManager::Instance()->isTIEntityRegistered(name)) {
        TIEntityFactory& factory = WorldManager::Instance()->getTIEntityFactory(name);
        WorldManager::Instance()->setLevelEntity(factory.build());
        return true;
    } else {
        LogManager::Instance()->warn("Level with name " + name + " is not registered.");
        return false;
    }
}


bool TIEngineInterface::registerTIEntityDefinition(const std::string& name, const sol::table& definition) {
    ScriptManager::Instance()->loadTIEntityDefinition(name, definition);
    return true;
}


TIEntityInterface TIEngineInterface::spawnTIEntity(const std::string& name) {
    if (WorldManager::Instance()->isTIEntityRegistered(name)) {
        TIEntity& tientity = WorldManager::Instance()->spawnTIEntity(name);
        return TIEntityInterface(tientity);
    } else {
        return nullptr;
    }
}


bool TIEngineInterface::hasEvent(std::string& event) {
    const sf::Event* eventPtr = EventsManager::Instance()->getEvent(String::stringToEvent(event));
    return eventPtr != nullptr;
}


Vector2iInterface TIEngineInterface::getMouseClickPosition() {
	const sf::Event* clickEvent = EventsManager::Instance()->getEvent(sf::Event::MouseButtonPressed);
    if (clickEvent != nullptr) {
        return Vector2iInterface(clickEvent->mouseButton.x, clickEvent->mouseButton.y);
    } else {
        return Vector2iInterface();
    }
}


TIEntityInterface TIEngineInterface::getTIEntityById(GlobalId id) {
    TIEntity* tientity = WorldManager::Instance()->getTIEntityById(id);
    if (tientity != nullptr) {
        return TIEntityInterface(tientity);
    } else {
        return nullptr;
    }
}


GlobalId TIEngineInterface::registerBehavior(const std::string& name, const sol::function& behavior) {
    return ScriptManager::Instance()->registerFunctionByName(name, behavior);
}
