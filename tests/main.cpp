#include "../src/managers/LogManager.h"
#include "../src/managers/PlayerManager.h"
#include "../src/managers/WindowManager.h"
#include "../src/managers/SceneObjectManager.h"
#include "../src/managers/SceneManager.h"
#include "../src/managers/InputManager.h"

#include "TestSceneObjectFactory.h"

int main()
{
	sf::RenderWindow& window = WindowManager::Instance()->addWindow();

	TestSceneObjectFactory f;
	const TestSceneObject& so1 = f.create();
	const TestSceneObject& so2 = f.create();

	so1.testAction(so2.getId());

	while (window.isOpen())
	{
		InputManager::Instance()->processInput();
		SceneObjectManager::Instance()->updateGameState();
		SceneManager::Instance()->render();		
	}
}
