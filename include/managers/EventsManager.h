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

namespace TIE {

class EventsManager : public Singleton<EventsManager>, public Manager {
	public:
		void processEvents();
		
		const sf::Vector2f& getMouseWindowPosition();
		const sf::Vector2f& getMouseWorldPosition();

		const std::vector<TIEntity*>& getTIEntitiesUnderMousePosition();

		bool hasEvents();
		const std::map<sf::Event::EventType, sf::Event>& getEvents();
		const sf::Event* const getEvent(const sf::Event::EventType&);
		void removeEvent(sf::Event::EventType);

		EventsManager() {};
		~EventsManager() {};

	private:
		void setTIEntitiesUnderMousePosition(TIEntity&, const sf::Vector2f&);
		
		ConsoleManager* consoleManager = ConsoleManager::Instance();

		sf::Vector2f mouseWindowPosition = sf::Vector2f(0, 0);
		sf::Vector2f mouseWorldPosition = sf::Vector2f(0, 0);

		std::map<sf::Event::EventType, sf::Event> events;
		std::vector<TIEntity*> tientitiesUnderMousePosition;

		EventsManager(const EventsManager&);
		void operator=(const EventsManager&) {};
};

}
#endif
