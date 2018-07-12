#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <memory>
#include <set>

#include "templates/Singleton.h"

#include "objects/SceneLayer.h"

namespace TIE {

class SceneManager : public Singleton<SceneManager> {
	public:
		SceneLayer& getSceneGraphRoot();
		SceneLayer& getEngineLayer();
		SceneLayer& getClientLayer();

		SceneNode* findSceneNode(sf::Vector2f);

		void removeNodes();
		void checkForCollisions();
		void updateGameState();
		void render();
	
		SceneManager();
		~SceneManager();
	private:
		sf::Clock& clock;
		float delta = 0;
		float TimePerFrame = 1.f/60.f; //Lock at 60 fps

		std::unique_ptr<SceneLayer> sceneGraphRoot;
		SceneLayer* engineLayer;
		SceneLayer* clientLayer;

		std::set<std::pair<SceneNode*, SceneNode*> > collisions;

		SceneManager(const SceneManager&);
		void operator=(const SceneManager&);
};

}
#endif
