/* This is where the lisence agreement would go.
 *
 * This is Twin Ion Engine, a game engine for the SFML graphics library.
 *
 * Glory and gore go hand in hand.
*/

#include "managers/EventsManager.h"
#include "managers/SceneManager.h"
#include "managers/StartUpManager.h"
#include "managers/TimeManager.h"
#include "managers/WindowManager.h"

int main() {
	TIE::StartUpManager::Instance()->initialize();
	
	sf::RenderWindow& window = TIE::WindowManager::Instance()->getWindow();

	sf::Clock& gameClock = TIE::TimeManager::Instance()->addClock();
	while (window.isOpen()) {
		if (gameClock.getElapsedTime().asSeconds() >= 0.01666666666f) { // 60 FPS frame rate
			TIE::EventsManager::Instance()->processEvents();
			TIE::SceneManager::Instance()->updateGameState(gameClock.restart().asSeconds());
		}
            
		TIE::SceneManager::Instance()->render();		

	}
}
