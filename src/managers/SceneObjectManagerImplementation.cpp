#include "../objects/SceneObject.h"

#include "SceneObjectManager.h"
#include "LogManager.h"

SceneObjectManager::SceneObjectManager() {}
SceneObjectManager::~SceneObjectManager() {}

void SceneObjectManager::addSceneObject()
{
	LogManager::Instance()->logInfo("Created SceneObject.");
	//create object
	//add to map
	//add to database
}

const SceneObject& SceneObjectManager::getSceneObject(int id)
{
	return SceneObjects[id];
}
