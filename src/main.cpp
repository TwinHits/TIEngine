#include <TIEngine.h>

int main() {
	TIE::StartUpManager::Instance()->initialize();
	
	sf::RenderWindow& window = TIE::WindowManager::Instance()->getWindow();

	while (window.isOpen()) {
		TIE::EventsManager::Instance()->processEvents();
		TIE::SceneManager::Instance()->updateGameState();
		TIE::SceneManager::Instance()->render();		
	}
}
