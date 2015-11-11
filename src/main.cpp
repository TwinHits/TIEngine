#include "managers/LogManager.h"
#include "managers/PlayerManager.h"
#include "managers/WindowManager.h"
#include "managers/SceneObjectManager.h"
#include "managers/SceneManager.h"
#include "managers/InputManager.h"
#include "managers/AssetsManager.h"

int main()
{
	LogManager::Instance()->logInfo("Program starting.");
	sf::RenderWindow& window = WindowManager::Instance()->addWindow();
	AssetsManager::Instance();
		

	PlayerManager::Instance()->addPlayer();
	SceneObjectManager::Instance()->addSceneObject();

	while (window.isOpen())
	{
		InputManager::Instance()->processInput();
		SceneObjectManager::Instance()->updateGameState();
		SceneManager::Instance()->render();		
	}

	LogManager::Instance()->logInfo("Program ended.");
}
