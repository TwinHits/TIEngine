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
		sf::RenderWindow& window = WindowManager::Instance()->getWindow();
		ConsoleManager* consoleManager = ConsoleManager::Instance();

		sf::Vector2f mouseWindowPosition = sf::Vector2f(0, 0);
		sf::Vector2f mouseWorldPosition = sf::Vector2f(0, 0);

		std::map<sf::Event::EventType, sf::Event> events;

		EventsManager(const EventsManager&);
		void operator=(const EventsManager&) {};
};

}
#endif
