#include "interfaces/TIEngineInterface.h"

#include <string>
#include <vector>

#include <sol/sol.hpp>

#include "componentsystems/MessagesComponentSystem.h"
#include "interfaces/MessageInterface.h"
#include "interfaces/TIEntityInterface.h"
#include "managers/AssetsManager.h"
#include "managers/EventsManager.h"
#include "managers/SceneManager.h"
#include "managers/ScriptManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"
#include "managers/WorldManager.h"
#include "objects/factories/SceneLayerFactory.h"
#include "objects/factories/ai/FiniteStateMachineFactory.h"
#include "utils/StringHelpers.h"

using namespace TIE;

void TIEngineInterface::registerUserType(sol::state& luaState) {

	sol::usertype<TIEngineInterface> engineInterfaceUserType = luaState.new_usertype<TIEngineInterface>("tiengine");
    engineInterfaceUserType["isValid"] = &TIEngineInterface::isValid;
    engineInterfaceUserType["registerTexturesDirectory"] = &TIEngineInterface::registerTexturesDirectory;
    engineInterfaceUserType["registerFontsDirectory"] = &TIEngineInterface::registerFontsDirectory;
    engineInterfaceUserType["registerAudioDirectory"] = &TIEngineInterface::registerAudioDirectory;
    engineInterfaceUserType["setWindowTitle"] = &TIEngineInterface::setWindowTitle;
    engineInterfaceUserType["setWindowSize"] = &TIEngineInterface::setWindowSize;
    engineInterfaceUserType["setWindowFullScreen"] = &TIEngineInterface::setWindowFullScreen;
    engineInterfaceUserType["setZoomSettings"] = &TIEngineInterface::setZoomSettings;
    engineInterfaceUserType["setLevel"] = &TIEngineInterface::setLevel;
	engineInterfaceUserType["spawn"] = &TIEngineInterface::spawn;
	engineInterfaceUserType["hasEvent"] = &TIEngineInterface::hasEvent;
	engineInterfaceUserType["getMouseClickPosition"] = &TIEngineInterface::getMouseClickPosition;
    engineInterfaceUserType["getTIEntityById"] = &TIEngineInterface::getTIEntityById;
    engineInterfaceUserType["registerSceneLayer"] = &TIEngineInterface::registerSceneLayer;
    engineInterfaceUserType["registerFiniteStateMachine"] = &TIEngineInterface::registerFiniteStateMachine;
    engineInterfaceUserType["registerMessageSubscription"] = &TIEngineInterface::registerMessageSubscription;
    engineInterfaceUserType["getMessageSubscriptions"] = &TIEngineInterface::getMessageSubscriptions;
    engineInterfaceUserType["getProperties"] = &TIEngineInterface::getProperties;
    engineInterfaceUserType["sendMessage"] = &TIEngineInterface::sendMessage;
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


void TIEngineInterface::setWindowFullScreen(const bool isFullscreen) {
	WindowManager::Instance()->updateFullScreen(isFullscreen);
}


bool TIEngineInterface::setLevel(const sol::table& level) {
    TIEntityFactory factory = TIEntityFactory();
    ScriptManager::Instance()->loadTIEntityDefinition(factory, level);
    WorldManager::Instance()->setLevelEntity(factory);
    return true;
}


bool TIEngineInterface::setZoomSettings(const float speed, const float minimum, const float maximum) {
    ViewManager::Instance()->setZoomSettings(speed, minimum, maximum);
    return true;
}


TIEntityInterface TIEngineInterface::spawn(const sol::table& definition) {
    TIEntityFactory factory = TIEntityFactory(definition);
    return TIEntityInterface(factory.build());
}


bool TIEngineInterface::hasEvent(std::string& event) {
    const sf::Event* eventPtr = EventsManager::Instance()->getEvent(String::stringToEvent(event));
    return eventPtr != nullptr;
}


const sf::Vector2i TIEngineInterface::getMouseClickPosition() {
    const sf::Event* clickEvent = EventsManager::Instance()->getEvent(sf::Event::MouseButtonPressed);
    if (clickEvent != nullptr) {
        return sf::Vector2i(clickEvent->mouseButton.x, clickEvent->mouseButton.y);
    } else {
        return sf::Vector2i(0,0);
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


TIEntityInterface TIEngineInterface::registerSceneLayer(const std::string& name, bool scrollable) {
    SceneLayerFactory sceneLayerFactory = SceneLayerFactory();
    sceneLayerFactory.setName(name);
    sceneLayerFactory.setParent(SceneManager::Instance()->getClientLayer());

    if (scrollable) {
        sceneLayerFactory.setViewId(ViewManager::Instance()->getClientViewId());
    } else {
        sceneLayerFactory.setViewId(ViewManager::Instance()->addView());
    }

    SceneLayer& sceneLayer = sceneLayerFactory.build();
    return TIEntityInterface(sceneLayer);
}


GlobalId TIEngineInterface::registerFiniteStateMachine(const sol::table& definition) {
    FiniteStateMachineFactory finiteStateMachineFactory = FiniteStateMachineFactory(definition);
    return finiteStateMachineFactory.getId();
}


GlobalId TIEngineInterface::registerMessageSubscription(const std::string& name) {
    return MessagesComponentSystem::Instance()->registerMessageSubscription(name);
}


const std::map<std::string, GlobalId>& TIEngineInterface::getMessageSubscriptions() {
    return MessagesComponentSystem::Instance()->getMessageSubscriptions();
}


const ComponentSystems::ComponentSystemPropertiesMap& TIEngineInterface::getProperties() {
    return SceneManager::Instance()->getComponentSystemPropertiesMap();
}


void TIEngineInterface::sendMessage(const GlobalId subscription, sol::object recievers, sol::object payload) {
    if (recievers.is<GlobalId>()) {
        MessagesComponentSystem::Instance()->sendMessage(subscription, 0, recievers.as<GlobalId>(), payload);
    } else if (recievers.is<sol::table>()) {
        for (auto& pair : recievers.as<sol::table>()) {
            const sol::object& reciever = pair.second;
            if (reciever.is<GlobalId>()) {
                MessagesComponentSystem::Instance()->sendMessage(subscription, 0, reciever.as<GlobalId>(), payload);
            }
        }
    }
}
