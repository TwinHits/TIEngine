#include "ConsoleManager.h"
#include "SceneManager.h"
#include "WindowManager.h"
#include "SceneObjectManager.h"
#include "TimeManager.h"

using namespace TIE;

SceneManager::SceneManager() : clock(TimeManager::Instance()->addClock())
{
}
	
SceneManager::~SceneManager() {}

void SceneManager::render()
{		
	
	sf::RenderWindow& window = WindowManager::Instance()->getWindow();
	auto sceneObjects = SceneObjectManager::Instance()->getAllSceneObjects();
	auto sceneTexts = SceneObjectManager::Instance()->getAllSceneTexts();

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

	//Draw DevConsole last because it's always on top.
	if (ConsoleManager::Instance()->checkConsole())
	{
		auto devConsole = ConsoleManager::Instance()->getDevConsole();
		window.draw(devConsole.getSprite());
		for (auto& st : devConsole.getCommandHistory())
			window.draw(st.getText());
	}

	window.display();

	auto frame = clock.restart().asSeconds();
	fps = 100 / frame;
	WindowManager::Instance()->showFPS(std::to_string(fps));
}

int SceneManager::getFPS()
{
	return fps;	
}
