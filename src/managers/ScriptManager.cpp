#include <string>
#include <vector>

#include "managers/ConfigManager.h"
#include "managers/LogManager.h"
#include "managers/SceneManager.h"
#include "managers/ScriptManager.h"
#include "managers/WindowManager.h"

#include "objects/components/SpriteComponent.h"
#include "objects/components/MovesComponent.h"

using namespace luabridge;
using namespace TIE;

ScriptManager::ScriptManager() {
    this->luaState = luaL_newstate();
    luaL_openlibs(this->luaState);
    Lua::loadGetKeysFunction(this->luaState);
}


void ScriptManager::loadScript(const std::string& scriptName) {
    const std::string& scriptsPath = ConfigManager::Instance()->getScriptsPath();
    std::string scriptFile = scriptsPath + scriptName;

    if (Lua::loadScript(this->luaState, scriptFile)) {

        std::vector<std::string> windowProperties = Lua::getTableKeys(this->luaState, "window");
        this->loadWindowProperties(windowProperties);

        std::vector<std::string> tientityKeys = Lua::getTableKeys(this->luaState, "tientities");
        this->loadTIEntityDefinitions(tientityKeys);
    }
}

void ScriptManager::loadWindowProperties(std::vector<std::string> windowProperties) {
    /*
    LuaRef titleProp = windowProperties["title"];
    LuaRef widthProp = windowProperties["width"];
    LuaRef heightProp = windowProperties["height"];

    std::string title = titleProp.cast<std::string>();
    int width = widthProp.cast<int>();
    int height = heightProp.cast<int>();
    WindowManager::Instance()->updateWindowSize(width, height);
    WindowManager::Instance()->setTitle(title);
    */
}

void ScriptManager::loadTIEntityDefinitions(std::vector<std::string> tientityKeys) {
}
