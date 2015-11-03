#ifndef EVENTSMANAGER_H
#define EVENTSMANAGER_H

#include <map>

#include <SFML/Graphics.hpp>

#include "../templates/Singleton.h"

class EventsManager : public Singleton<EventsManager>
{
	public:
		void processInput(const sf::Event& event);

		EventsManager();
		~EventsManager();
	private:
		std::map<unsigned int, unsigned int> keyBinds;

		EventsManager(const EventsManager&);
		void operator=(const EventsManager&);
};

#endif
