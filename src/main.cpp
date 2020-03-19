#include <TIEngine.h>

int main() {
	sf::RenderWindow& window = TIE::WindowManager::Instance()->getWindow();

	while (window.isOpen()) {
		TIE::InputManager::Instance()->processInput();
		TIE::SceneManager::Instance()->updateGameState();
		TIE::SceneManager::Instance()->render();		
	}
}
