#include <iostream>

#include "managers/LogManager.h"
#include "managers/ConfigManager.h"
#include "managers/AssetsManager.h"
#include "managers/HashManager.h"
#include "managers/WindowManager.h"
#include "managers/PlayerManager.h"
#include "managers/SceneObjectManager.h"
#include "managers/SceneManager.h"

int main()
{
	//auto logmanager = LogManager::Instance();
	//auto configmanager = ConfigManager::Instance();
	//auto assetsmanager = AssetsManager::Instance();
	//auto hashmanager = HashManager::Instance();
	//auto windowmanager = WindowManager::Instance();
	auto playermanager = PlayerManager::Instance();
	//auto sceneobjectmanager = SceneObjectManager::Instance();
	//auto scenemanager = SceneManager::Instance();

	const Player& player = playermanager->addPlayer();
	sf::RenderWindow& window = player.getWindow();

	sf::Sprite test;

	while (true)
	{
		window.clear();
		window.draw(test);
		window.display();
	}

	return 0;
}
