#include <iostream>

#include "managers/LogManager.h"
#include "managers/ConfigManager.h"
#include "managers/AssetsManager.h"
#include "managers/SceneObjectManager.h"
#include "managers/SceneManager.h"

int main()
{
	//auto logmanager = LogManager::Instance();
	//auto configmanager = ConfigManager::Instance();
	//auto assetsmanager = AssetsManager::Instance();
	auto sceneobjectmanager = SceneObjectManager::Instance();
	//auto scenemanager = SceneManager::Instance();

	sceneobjectmanager->addSceneObject();

	return 0;
}
