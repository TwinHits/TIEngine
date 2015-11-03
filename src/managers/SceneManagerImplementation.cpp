#include "SceneManager.h"
#include "WindowManager.h"
#include "SceneObjectManager.h"

SceneManager::SceneManager() {}
	
SceneManager::~SceneManager() {}

void SceneManager::render()
{		
	const std::map<unsigned long, RenderWindow*>& windows = WindowManager::Instance()->getAllWindows();
	const std::map<unsigned long, SceneObject*>& sceneObjects = SceneObjectManager::Instance()->getAllSceneObjects();

	for (auto w = windows.begin(); w != windows.end(); ++w)
	{
		w->second->clear();
		for (auto so = sceneObjects.begin(); so != sceneObjects.end(); ++so)
		{
			w->second->draw(so->second->getSprite());
		}
		w->second->display();
	}
	
}
