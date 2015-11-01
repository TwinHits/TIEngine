#include "managers/LogManager.h"
#include "managers/PlayerManager.h"
#include "managers/SceneObjectManager.h"
#include "managers/SceneManager.h"

int main()
{
	PlayerManager::Instance()->addPlayer();
	SceneObjectManager::Instance()->addSceneObject();

	while (true)
	{
		//ProcessInput
		//UpdateGameState
		SceneManager::Instance()->render();		
	}

	return 0;
}
