#include "SceneManager.h"
#include "WindowManager.h"
#include "SceneObjectManager.h"
#include "TimeManager.h"

SceneManager::SceneManager() 
{
	this->clock = TimeManager::Instance()->addClock();
}
	
SceneManager::~SceneManager() {}

void SceneManager::render()
{		
	
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();
	const std::map<GlobalId, SceneObject*>& sceneObjects = SceneObjectManager::Instance()->getAllSceneObjects();

	window.clear();
	for (auto so = sceneObjects.begin(); so != sceneObjects.end(); ++so)
	{
		if (so->second->getDraw())
			window.draw(so->second->getSprite());
	}
	window.display();

	double frame = clock.restart().asSeconds();
	fps = 100 / frame;

}

int SceneManager::getFPS()
{
	return fps;	
}
