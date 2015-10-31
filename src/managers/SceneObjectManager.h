#ifndef SCENEOBJECTMANAGER_H
#define SCENEOBJECTMANAGER_H

#include <map>

#include "../templates/Singleton.h"
#include "../objects/SceneObject.h"

class SceneObjectManager : public Singleton<SceneObjectManager>
{
	public:
		void addSceneObject();
		const SceneObject& getSceneObject(int id);

		SceneObjectManager();
		~SceneObjectManager();
	private:
		std::map<int, SceneObject> SceneObjects;
		
		SceneObjectManager(const SceneObjectManager&);
		void operator=(const SceneObjectManager&);
};

#endif
