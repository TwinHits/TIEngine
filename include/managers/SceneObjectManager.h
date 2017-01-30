#ifndef SCENEOBJECTMANAGER_H 
#define SCENEOBJECTMANAGER_H

#include <map>
#include <memory>

#include "../templates/Singleton.h"

#include "../objects/GlobalId.h"
#include "../objects/SceneObject.h"
#include "../objects/SceneText.h"

namespace TIE
{

	class SceneObjectManager : public Singleton<SceneObjectManager>
	{
		public:
			const SceneObject& addSceneObject(std::shared_ptr<SceneObject> so);
			void rmSceneObject(GlobalId id);

			const SceneText& addSceneText(std::shared_ptr<SceneText> st);
			void rmSceneText(GlobalId id);
		
			const SceneObject& getSceneObject(GlobalId id);
			const std::map<GlobalId, std::shared_ptr<SceneObject> >& getAllSceneObjects();

			const SceneText& getSceneText(GlobalId id);
			const std::map<GlobalId, std::shared_ptr<SceneText> >& getAllSceneTexts();

			void updateGameState();
		
			SceneObjectManager();
			~SceneObjectManager();
		private:
			std::map<GlobalId, std::shared_ptr<SceneObject> > sceneObjects;
			std::map<GlobalId, std::shared_ptr<SceneText> > sceneTexts;
		
			SceneObjectManager(const SceneObjectManager&);
			void operator=(const SceneObjectManager&);
	};

}
#endif
