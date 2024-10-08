#include "interfaces/TIEngineInterface.h"

#include <string>
#include <vector>

#include "componentsystems/BehavesComponentSystem.h"
#include "componentsystems/HoverableComponentSystem.h"
#include "interfaces/MessageInterface.h"
#include "interfaces/TIEntityInterface.h"
#include "managers/AssetsManager.h"
#include "managers/ComponentSystemsManager.h"
#include "managers/InputManager.h"
#include "managers/MessageManager.h"
#include "managers/SceneManager.h"
#include "managers/ScriptManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"
#include "managers/WorldManager.h"
#include "objects/factories/tientities/SceneLayerFactory.h"
#include "objects/factories/ai/FiniteStateMachineFactory.h"
#include "objects/factories/ai/BehaviorTreeNodeFactory.h"

using namespace TIE;

void TIEngineInterface::registerUserType(sol::state& luaState) {

	sol::usertype<TIEngineInterface> engineInterfaceUserType = luaState.new_usertype<TIEngineInterface>("tiengine");
    engineInterfaceUserType["isValid"] = &TIEngineInterface::isValid;
    engineInterfaceUserType["registerTexturesDirectory"] = &TIEngineInterface::registerTexturesDirectory;
    engineInterfaceUserType["registerFontsDirectory"] = &TIEngineInterface::registerFontsDirectory;
    engineInterfaceUserType["registerAudioDirectory"] = &TIEngineInterface::registerAudioDirectory;
    engineInterfaceUserType["setWindowTitle"] = &TIEngineInterface::setWindowTitle;
    engineInterfaceUserType["setWindowSize"] = &TIEngineInterface::setWindowSize;
    engineInterfaceUserType["getWindowSize"] = &TIEngineInterface::getWindowSize;
    engineInterfaceUserType["setWindowFullScreen"] = &TIEngineInterface::setWindowFullScreen;
    engineInterfaceUserType["setZoomSettings"] = &TIEngineInterface::setZoomSettings;
    engineInterfaceUserType["setLevel"] = &TIEngineInterface::setLevel;
	engineInterfaceUserType["spawn"] = &TIEngineInterface::spawn;
	engineInterfaceUserType["getMouseWorldPosition"] = &TIEngineInterface::getMouseWorldPosition;
    engineInterfaceUserType["getTIEntityById"] = &TIEngineInterface::getTIEntityById;
    engineInterfaceUserType["getTIEntitiesUnderCursor"] = &TIEngineInterface::getTIEntitiesUnderCursor;
    engineInterfaceUserType["registerSceneLayer"] = &TIEngineInterface::registerSceneLayer;
    engineInterfaceUserType["registerFiniteStateMachine"] = &TIEngineInterface::registerFiniteStateMachine;
    engineInterfaceUserType["registerBehaviorTreeNode"] = &TIEngineInterface::registerBehaviorTreeNode;
    engineInterfaceUserType["registerMessageSubscription"] = &TIEngineInterface::registerMessageSubscription;
    engineInterfaceUserType["getBehaviorTreeNodeTypes"] = &TIEngineInterface::getBehaviorTreeNodeTypes;
    engineInterfaceUserType["getBehaviorTreeDecoratorTypes"] = &TIEngineInterface::getBehaviorTreeDecoratorTypes;
    engineInterfaceUserType["getBehaviorTreeNodeStatuses"] = &TIEngineInterface::getBehaviorTreeNodeStatuses;
    engineInterfaceUserType["getMessageSubscriptions"] = &TIEngineInterface::getMessageSubscriptions;
    engineInterfaceUserType["getProperties"] = &TIEngineInterface::getProperties;
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


const sf::Vector2i& TIEngineInterface::getWindowSize() {
    return WindowManager::Instance()->getWindowSize();
}


bool TIEngineInterface::setWindowTitle(const std::string& title) {
	WindowManager::Instance()->setTitle(title);
    return true;
}


void TIEngineInterface::setWindowFullScreen(const bool isFullscreen) {
	WindowManager::Instance()->updateFullScreen(isFullscreen);
}


bool TIEngineInterface::setLevel(const sol::table& level) {
    TIEntityFactory factory = TIEntityFactory(level);
    WorldManager::Instance()->setLevelEntity(factory);
    return true;
}


bool TIEngineInterface::setZoomSettings(const float speed, const float minimum, const float maximum) {
    ViewManager::Instance()->setZoomSettings(speed, minimum, maximum);
    return true;
}


sol::object TIEngineInterface::spawn(const sol::table& definition) {
    TIEntityFactory factory = TIEntityFactory(definition);
    return ScriptManager::Instance()->getObjectFromValue(TIEntityInterface(factory.build()));
}


const sf::Vector2f TIEngineInterface::getMouseWorldPosition() {
    return InputManager::Instance()->getMouseWorldPosition();
}


sol::object TIEngineInterface::getTIEntityById(GlobalId id) {
    TIEntity* tientity = WorldManager::Instance()->getTIEntityById(id);
    if (tientity != nullptr) {
        return ScriptManager::Instance()->getObjectFromValue(TIEntityInterface(tientity));
    } else {
        return sol::nil;
    }
}


sol::object TIEngineInterface::getTIEntitiesUnderCursor() {
    const std::vector<std::reference_wrapper<TIEntity>>& tientities = HoverableComponentSystem::Instance()->getHoveredTIEntities();
    std::vector<TIEntityInterface> tientityInterfaces;
    for (auto& tientity : tientities) {
        tientityInterfaces.push_back(TIEntityInterface(tientity));
    }
    return ScriptManager::Instance()->getObjectFromValue(tientityInterfaces);
}


sol::object TIEngineInterface::registerSceneLayer(const std::string& name, bool scrollable) {
    SceneLayerFactory sceneLayerFactory = SceneLayerFactory();
    sceneLayerFactory.setName(name);
    sceneLayerFactory.setParent(SceneManager::Instance()->getClientLayer());

    if (scrollable) {
        sceneLayerFactory.setViewId(ViewManager::Instance()->getClientViewId());
    } else {
        sceneLayerFactory.setViewId(ViewManager::Instance()->addView());
    }

    SceneLayer& sceneLayer = sceneLayerFactory.build();
    return ScriptManager::Instance()->getObjectFromValue(TIEntityInterface(sceneLayer));
}


GlobalId TIEngineInterface::registerFiniteStateMachine(const sol::table& definition) {
    FiniteStateMachineFactory finiteStateMachineFactory = FiniteStateMachineFactory(definition);
    return finiteStateMachineFactory.getId();
}


GlobalId TIEngineInterface::registerBehaviorTreeNode(const sol::table& definition) {
    BehaviorTreeNodeFactory behaviorTreeNodeFactory = BehaviorTreeNodeFactory(definition);
    return behaviorTreeNodeFactory.getId();
}


const std::map<std::string, std::string>& TIEngineInterface::getBehaviorTreeNodeTypes() {
    return BehavesComponentSystem::Instance()->getBehaviorTreeNodeTypes();
}


const std::map<std::string, std::string>& TIEngineInterface::getBehaviorTreeDecoratorTypes() {
    return BehavesComponentSystem::Instance()->getBehaviorTreeDecoratorTypes();
}


const std::map<std::string, int>& TIEngineInterface::getBehaviorTreeNodeStatuses() {
    return BehavesComponentSystem::Instance()->getBehaviorTreeNodeStatuses();
}


GlobalId TIEngineInterface::registerMessageSubscription(const std::string& name) {
    return MessageManager::Instance()->getSubscriptionId(name);
}


const std::map<const std::string, GlobalId>& TIEngineInterface::getMessageSubscriptions() {
    return MessageManager::Instance()->getSubscriptionIds();
}


const ComponentSystems::ComponentSystemPropertiesMap& TIEngineInterface::getProperties() {
    return ComponentSystemsManager::Instance()->getComponentSystemPropertiesMap();
}
