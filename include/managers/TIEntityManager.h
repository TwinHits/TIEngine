#ifndef SCENEOBJECTMANAGER_H 
#define SCENEOBJECTMANAGER_H

#include <map>
#include <memory>

#include "templates/Singleton.h"

#include "objects/GlobalId.h"
#include "objects/SceneText.h"
#include "objects/TIEntity.h"

namespace TIE {

class TIEntityManager : public Singleton<TIEntityManager> {
	public:
		const TIEntity& addTIEntity(std::unique_ptr<TIEntity> so);
		void rmTIEntity(GlobalId id);

		const SceneText& addSceneText(std::unique_ptr<SceneText> st);
		void rmSceneText(GlobalId id);
	
		const TIEntity& getTIEntity(GlobalId id);
		const std::map<GlobalId, std::unique_ptr<TIEntity> >& getAllTIEntitys();

		const SceneText& getSceneText(GlobalId id);
		const std::map<GlobalId, std::unique_ptr<SceneText> >& getAllSceneTexts();

		void updateGameState();
	
		TIEntityManager();
		~TIEntityManager();
	private:
		std::map<GlobalId, std::unique_ptr<TIEntity> > sceneObjects;
		std::map<GlobalId, std::unique_ptr<SceneText> > sceneTexts;
		
		TIEntityManager(const TIEntityManager&);
		void operator=(const TIEntityManager&);
};

}
#endif
