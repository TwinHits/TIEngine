#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <memory>
#include <set>

#include "componentsystems/AnimatedComponentSystem.h"
#include "componentsystems/CollidesComponentSystem.h"
#include "componentsystems/EventsComponentSystem.h"
#include "componentsystems/GraphicsComponentSystem.h"
#include "componentsystems/MovesComponentSystem.h"
#include "componentsystems/SelectableComponentSystem.h"
#include "objects/SceneLayer.h"
#include "managers/WindowManager.h"

namespace TIE {

	class SceneManager : public Singleton<SceneManager>, Manager {
	public:
		bool initialize();

		SceneLayer& getSceneGraphRoot();
		SceneLayer& getEngineLayer();
		SceneLayer& getClientLayer();

		//Investigate with collides component
		//TIEntity* findTIEntity(sf::Vector2f);

		void updateGameState();
		void render();

		SceneManager();
		~SceneManager() {};
	private:
		WindowManager* windowManager = WindowManager::Instance();
		sf::RenderWindow& window = windowManager->getWindow();

		sf::Clock& clock;
		float delta = 0;

		std::unique_ptr<SceneLayer> sceneGraphRoot;
		SceneLayer* engineLayer = nullptr;
		SceneLayer* clientLayer = nullptr;

		AnimatedComponentSystem animatedComponentSystem = AnimatedComponentSystem();
		CollidesComponentSystem collidesComponentSystem = CollidesComponentSystem();
		EventsComponentSystem eventsComponentSystem = EventsComponentSystem();
		MovesComponentSystem movesComponentSystem = MovesComponentSystem();
		SelectableComponentSystem selectableComponentSystem = SelectableComponentSystem();

		void updateTIEntities(const std::vector<std::unique_ptr<TIEntity> >&);
		void removeTIEntities(std::vector<std::unique_ptr<TIEntity> >&);
		std::string calculateRollingAverageFPS(const float delta);

		SceneManager(const SceneManager&);
		void operator=(const SceneManager&) {};
};

}
#endif
