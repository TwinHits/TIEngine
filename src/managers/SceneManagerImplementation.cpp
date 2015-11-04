#include "SceneManager.h"
#include "WindowManager.h"
#include "SceneObjectManager.h"

SceneManager::SceneManager() {}
	
SceneManager::~SceneManager() {}

void SceneManager::render()
{		
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();
	const std::map<unsigned long, SceneObject*>& sceneObjects = SceneObjectManager::Instance()->getAllSceneObjects();

	window.clear();
	for (auto so = sceneObjects.begin(); so != sceneObjects.end(); ++so)
	{
		window.draw(so->second->getSprite());
	}
	window.display();
}
