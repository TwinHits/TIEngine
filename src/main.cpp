#include "../../TIEngine/src/TIEngine.h"

int main()
{
	//Minimum render loop
	sf::RenderWindow& window = TIE::WindowManager::Instance()->addWindow();

	while (window.isOpen())
	{
		TIE::InputManager::Instance()->processInput();
		TIE::SceneObjectManager::Instance()->updateGameState();
		TIE::SceneManager::Instance()->render();		
	}
}
