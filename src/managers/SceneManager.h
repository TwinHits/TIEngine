#ifndef SCENEMANAGER_H
#define SCENEMANGER_H

#include "../templates/Singleton.h"

class SceneManager : public Singleton<SceneManager>
{
	public:
		void draw();
		~SceneManager();
	private:
		SceneManager();
		SceneManager(const SceneManager&);
		void operator=(const SceneManager&);
};

#endif
