#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <map>

#include <SFML/Graphics.hpp>

#include <memory>

#include "../templates/Singleton.h"

#include "../objects/GlobalId.h"

namespace TIE
{
	enum Direction { TOP, RIGHT, BOTTOM, LEFT };

	class ViewManager : public Singleton<ViewManager>
	{
		public:
			GlobalId addView(const sf::FloatRect&);
			GlobalId addView();
			sf::View& getView(GlobalId);
			sf::View& getActiveView();
			void rmView(GlobalId);

			void updateCamera();
			void setActiveView(GlobalId);

			void scroll(Direction direction);
			void zoom(void);

			ViewManager();
			~ViewManager();

		private:
			std::map<GlobalId, std::shared_ptr<sf::View> > views;
			GlobalId activeView;

			void operator=(const ViewManager&);
			ViewManager(const ViewManager&);
	};
}

#endif
