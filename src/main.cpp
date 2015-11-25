#include "managers/WindowManager.h"
#include "managers/SceneObjectManager.h"
#include "managers/SceneManager.h"
#include "managers/InputManager.h"

int main()
{
	//Minimum render loop
	sf::RenderWindow& window = WindowManager::Instance()->addWindow();

	while (window.isOpen())
	{
		InputManager::Instance()->processInput();
		SceneObjectManager::Instance()->updateGameState();
		SceneManager::Instance()->render();		
	}
}
