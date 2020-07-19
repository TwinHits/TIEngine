#ifndef EVENTSMANAGER_H
#define EVENTSMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

namespace TIE {

class EventsManager : public Singleton<EventsManager>, Manager {
	public:
		bool initialize();

		void processEvents();
		
		const sf::Vector2f getMouseWindowPosition();
		const sf::Vector2f getMouseWorldPosition();

		const sf::Event* const getEvent(sf::Event::EventType);
		void removeEvent(sf::Event::EventType);

		EventsManager() {};
		~EventsManager() {};

	private:
		sf::Vector2f mouseWindowPosition;
		sf::Vector2f mouseWorldPosition;
		int scrollZone = 5;

		std::map<sf::Event::EventType, sf::Event> events;

		void scroll(sf::RenderWindow&);

		EventsManager(const EventsManager&);
		void operator=(const EventsManager&) {};
};

}
#endif
