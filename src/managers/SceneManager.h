#ifndef SCENEMANAGER_H
#define SCENEMANGER_H

#include "../templates/Singleton.h"

class SceneManager : public Singleton
{
	public:
		SceneManager();
		~SceneManager();
		void draw();
	private:
};

#endif
