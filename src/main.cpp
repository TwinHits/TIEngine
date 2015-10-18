#include <iostream>

#include "managers/SceneManager.h"

int main()
{
	SceneManager scenemanager = SceneManager();

	std::cout << &scenemanager << std::endl;

	return 0;
}
