#include "managers/LogManager.h"
#include "managers/PlayerManager.h"
#include "managers/WindowManager.h"
#include "managers/SceneObjectManager.h"
#include "managers/SceneManager.h"
#include "managers/EventsManager.h"

int main()
{
	LogManager::Instance()->logInfo("Program starting.");
	SceneObjectManager::Instance()->addSceneObject();
	sf::RenderWindow& window = WindowManager::Instance()->addWindow();

	while (window.isOpen())
	{
		EventsManager::Instance()->processInput();
		//update gamestate
		SceneManager::Instance()->render();		
	}

	LogManager::Instance()->logInfo("Program ended successfully.");
}
