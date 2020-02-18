#include <iostream>
#include <string>

#include "managers/ConfigManager.h"
#include "managers/LogManager.h"
#include "managers/ScriptManager.h"
#include "managers/WindowManager.h"
#include "managers/ViewManager.h"

using namespace luabridge;
using namespace TIE;

ScriptManager::ScriptManager() {
    this->luaState = luaL_newstate();
}


ScriptManager::~ScriptManager() {

}

void ScriptManager::loadScript(const std::string& scriptName) {

    const std::string& scriptsPath = ConfigManager::Instance()->getScriptsPath();
    std::string scriptFile = scriptsPath + scriptName;

    luaL_dofile(this->luaState, scriptFile.c_str());
    luaL_openlibs(this->luaState);
    lua_pcall(this->luaState, 0, 0, 0);

    LuaRef t = getGlobal(this->luaState, "window");
    LuaRef title = t["title"];
    LuaRef w = t["width"];
    LuaRef h = t["height"];
    std::string titleString = title.cast<std::string>();
    int width = w.cast<int>();
    int height = h.cast<int>();

    WindowManager::Instance()->addWindow(sf::VideoMode(width, height), titleString);
    TIE::GlobalId viewId = ViewManager::Instance()->addView();
    ViewManager::Instance()->setActiveView(viewId);
}
