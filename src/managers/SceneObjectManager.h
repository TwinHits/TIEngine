#ifndef SCENEOBJECTMANAGER_H 
#define SCENEOBJECTMANAGER_H

#include <map>
#include <memory>

#include "../templates/Singleton.h"

#include "../objects/GlobalId.h"
#include "../objects/SceneObject.h"

namespace TIE
{

	class SceneObjectManager : public Singleton<SceneObjectManager>
	{
		public:
			const SceneObject& addSceneObject(std::shared_ptr<SceneObject> so);
			void rmSceneObject(GlobalId id);
		
			const SceneObject& getSceneObject(GlobalId id);
			const std::map<GlobalId, std::shared_ptr<SceneObject> >& getAllSceneObjects();

			void updateGameState();
		
			SceneObjectManager();
			~SceneObjectManager();
		private:
			std::map<GlobalId, std::shared_ptr<SceneObject> > sceneObjects;
		
			SceneObjectManager(const SceneObjectManager&);
			void operator=(const SceneObjectManager&);
	};

}
#endif
