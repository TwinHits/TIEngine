#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <memory>

#include <SFML/Graphics.hpp>

#include "objects/tientities/common/SceneLayer.h"

namespace TIE {

	class SceneManager : public Singleton<SceneManager>, public Manager {
	public:
		void initialize();

		SceneLayer& getSceneGraphRoot();
		SceneLayer& getEngineLayer();
		SceneLayer& getClientLayer();

		void updateGameState(const float);
		void render();

		float getFPS();

		void setTIEntitiesMarkedForRemove(bool);

		const bool isSimulationPaused();

		SceneManager() {};
		~SceneManager() {};
	private:
		float calculateRollingAverageFPS(const float delta);
		float fps = 0;

		std::unique_ptr<SceneLayer> sceneGraphRoot;
		SceneLayer* engineLayer = nullptr;
		SceneLayer* clientLayer = nullptr;

		bool areTIEntitiesMarkedForRemove = false;
		bool simulationPaused = false;
		
		void removeTIEntities(TIEntity&);
		void render(TIEntity&, sf::RenderWindow&, sf::RenderStates);

		void toggleSimulationPaused();

		SceneManager(const SceneManager&);
		void operator=(const SceneManager&) {};
};

}
#endif
