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
			const sf::View& addView();
			const sf::View& getView(GlobalId);
			void rmView(GlobalId);
	
			ViewManager();
			~ViewManager();
		private:
			std::map<GlobalId, sf::View*> views;

			void operator=(const ViewManager&);
			ViewManager(const ViewManager&);
	};

}

#endif
