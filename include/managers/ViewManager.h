#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include "templates/Singleton.h"

#include <map>
#include <memory>

#include <SFML/Graphics.hpp>

#include "objects/GlobalId.h"
#include "objects/enumeration/Direction.h"

namespace TIE {

class ViewManager : public Singleton<ViewManager> {
	public:
		GlobalId addView();
		GlobalId addView(const sf::FloatRect&);
		sf::View& getView(GlobalId);
		sf::View& updateView(GlobalId, const sf::FloatRect&);
		sf::View& updateView(sf::View&, const sf::FloatRect&);
		void removeView(GlobalId);

		void updateCamera();
		void scroll(GlobalId viewId, Direction direction);
		void scroll(Direction direction);
		void zoom(void);

		void setActiveView(GlobalId);
		sf::View& getActiveView();

		void setScrollSpeed(float scrollSpeed);
		float getScrollSpeed();

		GlobalId getEngineViewId();
		GlobalId getClientViewId();

		sf::View& getEngineView();
		sf::View& getClientView();

		ViewManager();
		~ViewManager() {};

	private:
		std::map<GlobalId, std::unique_ptr<sf::View> > views;

		GlobalId activeViewId;
		GlobalId clientViewId;
		GlobalId engineViewId;

		float scrollSpeed = 5.0;
		
		void operator=(const ViewManager&) {};
		ViewManager(const ViewManager&);
};

}
#endif
