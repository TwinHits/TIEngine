
#include "../../TIEngine/src/TIEngine.h"

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
