#ifndef EVENTSMANAGER_H
#define EVENTSMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "managers/ConsoleManager.h"
#include "managers/WindowManager.h"
#include "managers/ViewManager.h"

namespace TIE {

class EventsManager : public Singleton<EventsManager>, Manager {
	public:
		bool initialize();

		void processEvents();
		
		const sf::Vector2f getMouseWindowPosition();
		const sf::Vector2f getMouseWorldPosition();

		const sf::Event* const getEvent(sf::Event::EventType);
		void removeEvent(sf::Event::EventType);

		void recalculateScrollZones();

		EventsManager() {};
		~EventsManager() {};

	private:
		sf::RenderWindow& window = WindowManager::Instance()->getWindow();
		ConsoleManager* consoleManager = ConsoleManager::Instance();
		ViewManager* viewManager = ViewManager::Instance();

		sf::View& clientView = viewManager->getClientView();
		GlobalId clientViewId = viewManager->getClientViewId();

		sf::Vector2f mouseWindowPosition;
		sf::Vector2f mouseWorldPosition;

		float scrollZone = 5.0;
		sf::FloatRect scrollUpZone;
		sf::FloatRect scrollLeftZone;
		sf::FloatRect scrollDownZone;
		sf::FloatRect scrollRightZone;

		std::map<sf::Event::EventType, sf::Event> events;

		void scroll();

		EventsManager(const EventsManager&);
		void operator=(const EventsManager&) {};
};

}
#endif
