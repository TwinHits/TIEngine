#include "interfaces/TIEngineInterface.h"

#include <string>

#include <sol/sol.hpp>

#include "managers/AssetsManager.h"
#include "managers/ScriptManagerV2.h"
#include "managers/WindowManager.h"
#include "managers/WorldManager.h"

using namespace TIE;

TIEngineInterface::TIEngineInterface(sol::state& luaState) {
	sol::usertype<TIEngineInterface> engineInterfaceUserType = luaState.new_usertype<TIEngineInterface>("tiengine");
    engineInterfaceUserType["isValid"] = &TIEngineInterface::isValid;
    engineInterfaceUserType["registerTexturesDirectory"] = &TIEngineInterface::registerTexturesDirectory;
    engineInterfaceUserType["registerFontDirectory"] = &TIEngineInterface::registerFontsDirectory;
    engineInterfaceUserType["registerAudioDirectory"] = &TIEngineInterface::registerAudioDirectory;
    engineInterfaceUserType["setWindowTitle"] = &TIEngineInterface::setWindowTitle;
    engineInterfaceUserType["setWindowSize"] = &TIEngineInterface::setWindowSize;
	engineInterfaceUserType["registerTIEntity"] = &TIEngineInterface::registerTIEntityDefinition;
	engineInterfaceUserType["spawn"] = &TIEngineInterface::spawnTIEntity;
}


bool TIEngineInterface::isValid() {
    return this != nullptr;
}


bool TIEngineInterface::registerTexturesDirectory(const std::string& directory) {
    return AssetsManager::Instance()->loadTexturesFromPath(ScriptManagerV2::Instance()->getScriptWorkingDirectory() + directory);
}


bool TIEngineInterface::registerFontsDirectory(const std::string& directory) {
    return AssetsManager::Instance()->loadFontsFromPath(ScriptManagerV2::Instance()->getScriptWorkingDirectory() + directory);
}


bool TIEngineInterface::registerAudioDirectory(const std::string& directory) {
    return AssetsManager::Instance()->loadAudioFromPath(ScriptManagerV2::Instance()->getScriptWorkingDirectory() + directory);
}


bool TIEngineInterface::setWindowSize(const int width, const int height) {
	WindowManager::Instance()->updateWindowSize(width, height);
    return true;
}


bool TIEngineInterface::setWindowTitle(const std::string& title) {
	WindowManager::Instance()->setTitle(title);
    return true;
}


bool TIEngineInterface::registerTIEntityDefinition(const std::string& name, const sol::table& definition) {
    ScriptManagerV2::Instance()->loadTIEntityDefinition(name, definition);
    return true;
}


bool TIEngineInterface::spawnTIEntity(const std::string& name) {
    WorldManager::Instance()->spawnTIEntity(name);
    return true;
}

