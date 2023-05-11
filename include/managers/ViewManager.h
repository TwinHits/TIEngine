#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <map>
#include <memory>

#include <SFML/Graphics.hpp>

#include "managers/ConsoleManager.h"
#include "managers/EventsManager.h"
#include "objects/GlobalId.h"
#include "objects/enumeration/Direction.h"

namespace TIE {

class ViewManager : public Singleton<ViewManager>, Manager {
	public:
		bool initialize();
		
		GlobalId addView();
		GlobalId addView(const sf::FloatRect&);
		sf::View& getView(GlobalId);
		sf::View& updateView(GlobalId, const sf::Vector2i&);
		sf::View& updateView(sf::View&, const sf::Vector2i&);
		sf::View& updateView(GlobalId, const sf::FloatRect&);
		sf::View& updateView(sf::View&, const sf::FloatRect&);
		void updateViews(const sf::Vector2i&);
		void removeView(GlobalId);

		void updateCamera(const float);
		void recalculateScrollZones(const sf::Vector2i&);

		void setActiveView(GlobalId);
		sf::View& getActiveView();

		GlobalId getEngineViewId();
		GlobalId getClientViewId();

		sf::View& getEngineView();
		sf::View& getClientView();

		void setScrollBounds(const sf::FloatRect&);
		const sf::FloatRect& getScrollBounds();

		bool isViewIdScrollable(const GlobalId);

		void setZoomSettings(const float, const float, const float);

		void onWindowSizeChange();

		ViewManager() {};
		~ViewManager() {};

	private:
		const sf::Vector2f calculateClientScroll(const sf::Vector2f, const float);
		const sf::Vector2f calculateEngineScroll(const sf::Vector2f&, const float);
		void zoomCamera(const float);

		EventsManager* eventsManager = EventsManager::Instance();
		ConsoleManager* consoleManager = ConsoleManager::Instance();

		std::map<GlobalId, std::unique_ptr<sf::View> > views;

		GlobalId activeViewId = 0;
		GlobalId clientViewId = 0;
		GlobalId engineViewId = 0;

		sf::View* clientView = nullptr;
		sf::View* engineView = nullptr;

		float scrollZone = 2.0;
		float scrollSpeed = 500.0;
		sf::FloatRect scrollUpZone;
		sf::FloatRect scrollLeftZone;
		sf::FloatRect scrollDownZone;
		sf::FloatRect scrollRightZone;
		sf::FloatRect scrollBounds;

		float currentZoom = 1.0f;
		float zoomSpeed = 0.0f;
		float zoomMinimum = 0.0f;
		float zoomMaximum = 1.0f;

		void operator=(const ViewManager&) {};
		ViewManager(const ViewManager&);
};

}
#endif
