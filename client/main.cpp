#include "TestSceneObjectFactory.h"
#include "TestSceneObject.h"

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
