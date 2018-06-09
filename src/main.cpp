#include "TIEngine.h"

int main()
{
	//Minimum render loop for sample
	sf::RenderWindow& window = TIE::WindowManager::Instance()->addWindow();

	while (window.isOpen()) {
		TIE::InputManager::Instance()->processInput();
		TIE::TIEntityManager::Instance()->updateGameState();
		TIE::SceneManager::Instance()->render();		
	}
}
