#ifndef SCENEOBJECTMANAGER_H 
#define SCENEOBJECTMANAGER_H

#include <memory>
#include <set>

#include "templates/Singleton.h"

#include "objects/GlobalId.h"
#include "objects/SceneLayer.h"
#include "objects/drawables/TIEntity.h"

namespace TIE {

class TIEntityManager : public Singleton<TIEntityManager> {
	public:
		SceneLayer& getSceneGraphRoot();
		SceneLayer& getEngineLayer();
		SceneLayer& getClientLayer();

		void checkForCollisions();
		void updateGameState();
		void removeNodes();
	
		TIEntityManager();
		~TIEntityManager();
	private:
		sf::Clock& clock;
		float delta = 0;
		float TimePerFrame = 1.f/60.f; //Lock at 60 fps

		std::unique_ptr<SceneLayer> sceneGraphRoot;
		SceneLayer* engineLayer;
		SceneLayer* clientLayer;

		std::set<std::pair<SceneNode*, SceneNode*> > collisions;

		TIEntityManager(const TIEntityManager&);
		void operator=(const TIEntityManager&);
};

}
#endif
