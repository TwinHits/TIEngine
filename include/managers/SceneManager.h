#ifndef SCENEMANAGER_H
#define SCENEMANGER_H

#include "TimeManager.h"

#include "templates/Singleton.h"

namespace TIE {

class SceneManager : public Singleton<SceneManager> {
	public:
		void render();

		~SceneManager();
		SceneManager();
	private:
		GlobalId sceneViewId;

		SceneManager(const SceneManager&);
		void operator=(const SceneManager&);
};

}
#endif
