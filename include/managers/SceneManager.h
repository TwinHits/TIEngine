#ifndef SCENEMANAGER_H
#define SCENEMANGER_H

#include "TimeManager.h"

#include "templates/Singleton.h"

namespace TIE
{

	class SceneManager : public Singleton<SceneManager>
	{
		public:
			void render();
			double getFPS();

			~SceneManager();
			SceneManager();
		private:
			sf::Clock& clock;
			double fps;
			GlobalId sceneViewId;

			SceneManager(const SceneManager&);
			void operator=(const SceneManager&);
	};

}
#endif
