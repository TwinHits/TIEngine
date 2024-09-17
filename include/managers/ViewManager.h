#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <map>
#include <memory>

#include <SFML/Graphics.hpp>

#include "enumeration/Direction.h"
#include "managers/ConsoleManager.h"
#include "managers/InputManager.h"
#include "objects/GlobalId.h"

namespace TIE {

class ViewManager : public Singleton<ViewManager>, public Manager {
	public:
		void initialize();
		
		GlobalId addView();
		GlobalId addView(const sf::FloatRect&);
		GlobalId addView(const sf::FloatRect&, const sf::FloatRect&);
		sf::View& getView(GlobalId);
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


		ViewManager() {};
		~ViewManager() {};

	private:
		const sf::Vector2f calculateClientScroll(const sf::Vector2f, const float);

		sf::View& updateView(sf::View&, const sf::FloatRect&);
		sf::View& updateView(sf::View&, const sf::FloatRect&, const sf::Vector2i);
		void updateViews(const sf::Vector2i&);

		void onMouseWheelMoved();
		void onWindowSizeChange();

		InputManager* inputManager = InputManager::Instance();
		ConsoleManager* consoleManager = ConsoleManager::Instance();

		std::map<GlobalId, std::unique_ptr<sf::View> > views;
		std::map<GlobalId, sf::FloatRect> viewSizes;

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
