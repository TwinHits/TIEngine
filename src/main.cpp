#include "managers/LogManager.h"
#include "managers/PlayerManager.h"
#include "managers/WindowManager.h"
#include "managers/SceneObjectManager.h"
#include "managers/SceneManager.h"
#include "managers/InputManager.h"

int main()
{
	sf::RenderWindow& window = WindowManager::Instance()->addWindow();

	PlayerManager::Instance()->addPlayer();
	auto so1 = SceneObjectManager::Instance()->addSceneObject();
	auto so2 = SceneObjectManager::Instance()->addSceneObject();

	so1.action(so2);

	while (window.isOpen())
	{
		InputManager::Instance()->processInput();
		SceneObjectManager::Instance()->updateGameState();
		SceneManager::Instance()->render();		
	}
}
