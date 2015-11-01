#include "SceneManager.h"
#include "PlayerManager.h"
#include "SceneObjectManager.h"


SceneManager::SceneManager() {}
	
SceneManager::~SceneManager() {}

void SceneManager::render()
{		
	const std::map<unsigned long, Player*>& players = PlayerManager::Instance()->getAllPlayers();
	const std::map<unsigned long, SceneObject*>& sceneObjects = SceneObjectManager::Instance()->getAllSceneObjects();

	for (auto p = players.begin(); p != players.end(); ++p)
	{
		sf::RenderWindow& window = p->second->getWindow();
		window.clear();
		for (auto so = sceneObjects.begin(); so != sceneObjects.end(); ++so)
		{
			window.draw(so->second->getSprite());
		}
		window.display();
	}
	
}
