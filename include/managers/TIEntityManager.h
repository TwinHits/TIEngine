#ifndef SCENEOBJECTMANAGER_H 
#define SCENEOBJECTMANAGER_H

#include <map>
#include <memory>

#include "templates/Singleton.h"

#include "objects/GlobalId.h"
#include "objects/SceneLayer.h"
#include "objects/drawables/TIEntity.h"

namespace TIE {

enum DetectionStrategy { SIMPLE };

class TIEntityManager : public Singleton<TIEntityManager> {
	public:
		SceneLayer& getSceneGraphRoot();
		SceneLayer& getEngineLayer();
		SceneLayer& getClientLayer();

		std::vector<GlobalId> getCollidingTIEntities(DetectionStrategy strategy, TIEntity& entity);

		void updateGameState();
	
		TIEntityManager();
		~TIEntityManager();
	private:
		sf::Clock& clock;
		float delta = 0;
		float TimePerFrame = 1.f/60.f; //Lock at 60 fps

		std::unique_ptr<SceneLayer> sceneGraphRoot;
		SceneLayer* engineLayer;
		SceneLayer* clientLayer;

		//Strategy Pattern
		void simple(std::vector<GlobalId>&, TIEntity& entity);
		
		TIEntityManager(const TIEntityManager&);
		void operator=(const TIEntityManager&);
};

}
#endif
