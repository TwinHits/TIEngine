#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <map>

#include <SFML/Graphics.hpp>

#include "../templates/Singleton.h"

#include "../objects/GlobalId.h"

namespace TIE
{
	class ViewManager : public Singleton<ViewManager>
	{
		public:
			GlobalId addView(const sf::FloatRect&);
			GlobalId addView();
			sf::View& getView(GlobalId);
			sf::View& getCurrentView();
			void rmView(GlobalId);

			void updateCamera();
			void changeCurrentView(GlobalId);

			void scroll(int direction);

			ViewManager();
			~ViewManager();

		private:
			std::map<GlobalId, sf::View*> views;
			GlobalId activeView;

			void operator=(const ViewManager&);
			ViewManager(const ViewManager&);
	};

	enum Direction { TOP, RIGHT, BOTTOM, LEFT };
}

#endif
