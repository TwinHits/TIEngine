/* This is where the lisence agreement would go.
 *
 * This is Twin Ion Engine, a game engine for the SFML graphics library.
 * Include this file, in order to access all the neccessary classes to utilize
 * this libray.
 * * See src/main.cpp for an example of the basic render loop.
 *
 * Glory and gore go hand in hand.
*/

#include "managers/EventsManager.h"
#include "managers/SceneManager.h"
#include "managers/StartUpManager.h"
#include "managers/WindowManager.h"

int main() {
	TIE::StartUpManager::Instance()->initialize();
	
	sf::RenderWindow& window = TIE::WindowManager::Instance()->getWindow();

	while (window.isOpen()) {
		TIE::EventsManager::Instance()->processEvents();
		TIE::SceneManager::Instance()->updateGameState();
		TIE::SceneManager::Instance()->render();		
	}
}
