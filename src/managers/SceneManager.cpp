#include "managers/ConsoleManager.h"
#include "managers/SceneManager.h"
#include "managers/WindowManager.h"
#include "managers/TIEntityManager.h"
#include "managers/TimeManager.h"
#include "managers/ViewManager.h"


using namespace TIE;


SceneManager::SceneManager() : clock(TimeManager::Instance()->addClock())
{
	sceneViewId = ViewManager::Instance()->addView(sf::FloatRect(0,0,800,600));

}

	
SceneManager::~SceneManager() 
{

}


void SceneManager::render()
{		
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();
   	ViewManager::Instance()->setActiveView(sceneViewId);

	auto sceneObjects = TIEntityManager::Instance()->getAllTIEntitys();
	auto sceneTexts = TIEntityManager::Instance()->getAllSceneTexts();

	window.clear();
	for (auto& so : sceneObjects)
	{
		if (so.second->getDraw())
			window.draw(so.second->getSprite());
	}

	for (auto& st : sceneTexts)
	{
		if (st.second->getDraw())
			window.draw(st.second->getText());
	}
	
	if (ConsoleManager::Instance()->checkConsole())
		ConsoleManager::Instance()->renderDevConsole();

	window.display();

	auto frame = clock.restart().asSeconds();
	this->fps = 60 / frame;
	WindowManager::Instance()->showFPS(std::to_string(fps));
}


double SceneManager::getFPS()
{
	return fps;	
}