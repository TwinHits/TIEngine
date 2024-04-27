#include "managers/StartUpManager.h"

#include "managers/AssetsManager.h"
#include "managers/ComponentSystemsManager.h"
#include "managers/ConfigManager.h"
#include "managers/ConsoleManager.h"
#include "managers/InputManager.h"
#include "managers/WorldManager.h"
#include "managers/HashManager.h"
#include "managers/LogManager.h"
#include "managers/MessageManager.h"
#include "managers/SceneManager.h"
#include "managers/ScriptManager.h"
#include "managers/TimeManager.h"
#include "managers/UIManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"

using namespace TIE;

void StartUpManager::initialize() {
	WindowManager::Instance()->initialize();
	ConfigManager::Instance()->initialize();
	LogManager::Instance()->initialize();
	AssetsManager::Instance()->initialize();
	MessageManager::Instance()->initialize();
	ViewManager::Instance()->initialize();
	InputManager::Instance()->initialize();
	SceneManager::Instance()->initialize();
	ComponentSystemsManager::Instance()->initialize();
	ConsoleManager::Instance()->initialize();
	HashManager::Instance()->initialize();
	TimeManager::Instance()->initialize();
	WorldManager::Instance()->initialize();
	UIManager::Instance()->initialize();
	ScriptManager::Instance()->initialize();
}
