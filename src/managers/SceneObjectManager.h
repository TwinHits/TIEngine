#ifndef SCENEOBJECTMANAGER_H 
#define SCENEOBJECTMANAGER_H

#include <map>

#include "../templates/Singleton.h"

#include "../objects/GlobalId.h"
#include "../objects/SceneObject.h"

namespace TIE
{

	class SceneObjectManager : public Singleton<SceneObjectManager>
	{
		public:
			const SceneObject& addSceneObject(SceneObject* so);
			void rmSceneObject(GlobalId id);
		
			const SceneObject& getSceneObject(GlobalId id);
			const std::map<GlobalId, SceneObject*>& getAllSceneObjects();

			void updateGameState();
		
			SceneObjectManager();
			~SceneObjectManager();
		private:
			std::map<GlobalId, SceneObject*> sceneObjects;
		
			SceneObjectManager(const SceneObjectManager&);
			void operator=(const SceneObjectManager&);
	};

}
#endif
