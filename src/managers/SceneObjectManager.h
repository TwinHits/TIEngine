#ifndef SCENEOBJECTMANAGER_H 
#define SCENEOBJECTMANAGER_H

#include <map>

#include "../templates/Singleton.h"
#include "../objects/SceneObject.h"

class SceneObjectManager : public Singleton<SceneObjectManager>
{
	public:
		const SceneObject& addSceneObject();
		const SceneObject& getSceneObject(unsigned long id);
		void rmSceneObject(unsigned long id);

		SceneObjectManager();
		~SceneObjectManager();
	private:
		std::map<unsigned long, SceneObject*> sceneObjects;
		
		SceneObjectManager(const SceneObjectManager&);
		void operator=(const SceneObjectManager&);
};

#endif
