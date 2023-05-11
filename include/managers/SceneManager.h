#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <memory>
#include <vector>

#include "componentsystems/ComponentSystem.h"
#include "managers/WindowManager.h"
#include "objects/tientities/SceneLayer.h"

namespace TIE {

	class SceneManager : public Singleton<SceneManager>, public Manager {
	public:
		void initialize();

		SceneLayer& getSceneGraphRoot();
		SceneLayer& getEngineLayer();
		SceneLayer& getClientLayer();

		const std::vector<ComponentSystem*>& getComponentSystems();
		bool isValidComponentName(const std::string&);
		ComponentSystem* getComponentSystemByComponentName(const std::string&);
		const ComponentSystems::ComponentSystemPropertiesMap& getComponentSystemPropertiesMap();

		void updateGameState(const float);
		void render();

		float getFPS();

		void setTIEntitiesMarkedForRemove(bool);

		void setSimulationPaused(const bool);
		const bool getSimulationPaused();

		SceneManager() {};
		~SceneManager() {};
	private:
		float calculateRollingAverageFPS(const float delta);
		float fps = 0;

		std::unique_ptr<SceneLayer> sceneGraphRoot;
		SceneLayer* engineLayer = nullptr;
		SceneLayer* clientLayer = nullptr;

		std::vector<ComponentSystem*> componentSystems;
		std::map<std::string, ComponentSystem*> componentNamesToComponentSystems;
		ComponentSystems::ComponentSystemPropertiesMap componentSystemPropertiesMap;

		bool tientitiesMarkedForRemove = false;
		bool simulationPaused = false;
		
		void removeTIEntities(TIEntity&);
		void removeComponents(TIEntity&);
		void updateEngineEntities(TIEntity&, const float);
		void render(TIEntity&, sf::RenderWindow&, sf::RenderStates);

		SceneManager(const SceneManager&);
		void operator=(const SceneManager&) {};
};

}
#endif
