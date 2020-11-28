#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "componentsystems/ComponentSystem.h"
#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <memory>
#include <vector>

#include "objects/SceneLayer.h"
#include "managers/WindowManager.h"

namespace TIE {

	class SceneManager : public Singleton<SceneManager>, Manager {
	public:
		bool initialize();

		SceneLayer& getSceneGraphRoot();
		SceneLayer& getEngineLayer();
		SceneLayer& getClientLayer();

		const std::vector<ComponentSystem*>& getComponentSystems();

		//Investigate with collides component
		//TIEntity* findTIEntity(sf::Vector2f);

		void updateGameState();
		void render();

		float getFPS();

		SceneManager();
		~SceneManager() {};
	private:
		WindowManager* windowManager = WindowManager::Instance();
		sf::RenderWindow& window = windowManager->getWindow();

		sf::Clock& clock;
		float calculateRollingAverageFPS(const float delta);
		float fps = 0;
		float delta = 0;

		std::unique_ptr<SceneLayer> sceneGraphRoot;
		SceneLayer* engineLayer = nullptr;
		SceneLayer* clientLayer = nullptr;

		std::vector<ComponentSystem*> componentSystems;

		void updateEngineEntity(TIEntity&);
		void removeTIEntities(std::vector<std::unique_ptr<TIEntity> >&);
		void render(TIEntity&, sf::RenderWindow&, sf::RenderStates);

		SceneManager(const SceneManager&);
		void operator=(const SceneManager&) {};
};

}
#endif
