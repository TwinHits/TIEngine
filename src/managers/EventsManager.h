#ifndef EVENTSMANAGER_H
#define EVENTSMANAGER_H

#include <map>

#include "../templates/Singleton.h"

class EventsManager : public Singleton<EventsManager>
{
	public:
		void processInput();

		EventsManager();
		~EventsManager();
	private:
		std::map<unsigned int, unsigned int> keyBinds;

		EventsManager(const EventsManager&);
		void operator=(const EventsManager&);
};

#endif
