#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <map>

#include <SFML/Graphics.hpp>

#include <memory>

#include "templates/Singleton.h"

#include "objects/Direction.h"
#include "objects/GlobalId.h"

namespace TIE {
	

class ViewManager : public Singleton<ViewManager> {
	public:
		GlobalId addView(const sf::FloatRect&);
		GlobalId addView();
		sf::View& getView(GlobalId);
		sf::View& getActiveView();
		void removeView(GlobalId);


		void setActiveView(GlobalId);
		void updateCamera();

		void setScrollSpeed(float scrollSpeed);
		float getScrollSpeed();

		void scroll(Direction direction);
		void zoom(void);

		ViewManager();
		~ViewManager();

	private:
		std::map<GlobalId, std::unique_ptr<sf::View> > views;
		GlobalId activeView;

		float scrollSpeed = 5.0;
		
		void operator=(const ViewManager&);
		ViewManager(const ViewManager&);
};

}
#endif
