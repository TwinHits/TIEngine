#include <iostream>

#include "managers/SceneManager.h"

int main()
{
	std::shared_ptr<SceneManager> scenemanager1 = SceneManager::Instance();
	std::shared_ptr<SceneManager> scenemanager2 = SceneManager::Instance();

	if (scenemanager1 == scenemanager2) 
	{
		std::cout << "true" << std::endl;
	}
	else
	{
		std::cout << "false" << std::endl;
	}

	return 0;
}
