#include "SceneManager.h"
#include "WindowManager.h"
#include "SceneObjectManager.h"
#include "TimeManager.h"

using namespace TIE;

SceneManager::SceneManager() 
{
	this->clock = TimeManager::Instance()->addClock();
}
	
SceneManager::~SceneManager() {}

void SceneManager::render()
{		
	
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();
	auto sceneObjects = SceneObjectManager::Instance()->getAllSceneObjects();

	window.clear();
	for (auto& so : sceneObjects)
	{
		if (so.second->getDraw())
			window.draw(so.second->getSprite());
	}
	window.display();

	double frame = clock.restart().asSeconds();
	fps = 100 / frame;
	WindowManager::Instance()->showFPS(std::to_string(fps));
}

int SceneManager::getFPS()
{
	return fps;	
}
