#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "templates/Singleton.h"

#include <memory>
#include <set>

#include "managers/componentsystems/ComponentSystem.h" 
#include "objects/SceneLayer.h"

namespace TIE {

	class SceneManager : public Singleton<SceneManager> {
	public:
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
		sf::Clock& clock;
		float delta = 0;
		float TimePerFrame = 1.f / 60.f; //Lock at 60 fps

		std::unique_ptr<SceneLayer> sceneGraphRoot;
		SceneLayer* engineLayer;
		SceneLayer* clientLayer;

		void executeComponentSystems(const std::vector<std::unique_ptr<TIEntity> >&);
		void removeTIEntities(std::vector<std::unique_ptr<TIEntity> >&);

		SceneManager(const SceneManager&);
		void operator=(const SceneManager&) {};
};

}
#endif
