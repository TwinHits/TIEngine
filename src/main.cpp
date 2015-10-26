#include <iostream>

#include "managers/SceneManager.h"

int main()
{
	auto scenemanager = SceneManager::Instance();
	auto scenemanager2 = SceneManager::Instance();

	std::cout << scenemanager << std::endl;
	std::cout << scenemanager2 << std::endl;

	return 0;
}
