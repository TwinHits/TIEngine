#ifndef SCENEOBJECTMANAGER_H 
#define SCENEOBJECTMANAGER_H

#include <map>
#include <memory>
#include <queue>

#include "templates/Singleton.h"

#include "objects/GlobalId.h"
#include "objects/TIEntity.h"
#include "objects/SceneText.h"

namespace TIE
{

	class TIEntityManager : public Singleton<TIEntityManager>
	{
		public:
			const TIEntity& addTIEntity(std::shared_ptr<TIEntity> so);
			void rmTIEntity(GlobalId id);

			const SceneText& addSceneText(std::shared_ptr<SceneText> st);
			void rmSceneText(GlobalId id);
		
			const TIEntity& getTIEntity(GlobalId id);
			const std::map<GlobalId, std::shared_ptr<TIEntity> >& getAllTIEntitys();

			const SceneText& getSceneText(GlobalId id);
			const std::map<GlobalId, std::shared_ptr<SceneText> >& getAllSceneTexts();

			void updateGameState();
		
			TIEntityManager();
			~TIEntityManager();
		private:
			std::map<GlobalId, std::shared_ptr<TIEntity> > sceneObjects;
			std::map<GlobalId, std::shared_ptr<SceneText> > sceneTexts;
			
			std::priority_queue<std::shared_ptr<TIEntity> > objectsToBeDrawn();
		
			TIEntityManager(const TIEntityManager&);
			void operator=(const TIEntityManager&);
	};

}
#endif
