#include "managers/StartUpManager.h"

#include "managers/AssetsManager.h"
#include "managers/ConfigManager.h"
#include "managers/ConsoleManager.h"
#include "managers/EventsManager.h"
#include "managers/WorldManager.h"
#include "managers/HashManager.h"
#include "managers/LogManager.h"
#include "managers/SceneManager.h"
#include "managers/ScriptManagerV2.h"
#include "managers/StringManager.h"
#include "managers/TimeManager.h"
#include "managers/ViewManager.h"
#include "managers/WindowManager.h"

using namespace TIE;

bool StartUpManager::initialize() {

	WindowManager::Instance()->initialize();
	ConfigManager::Instance()->initialize();
	LogManager::Instance()->initialize();
	AssetsManager::Instance()->initialize();
	ViewManager::Instance()->initialize();
	EventsManager::Instance()->initialize();
	SceneManager::Instance()->initialize();
	ConsoleManager::Instance()->initialize();
	HashManager::Instance()->initialize();
	TimeManager::Instance()->initialize();
	ScriptManagerV2::Instance()->initialize();
	StringManager::Instance()->initialize();
	WorldManager::Instance()->initialize();

	return true;
}
