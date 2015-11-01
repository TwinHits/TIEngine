#ifndef EVENTSMANAGER_H
#define EVENTSMANAGER_H

#include "../templates/Singleton.h"

class EventsManager : public Singleton<EventsManager>
{
	public:
		EventsManager();
		~EventsManager();
	private:
		EventsManager(const EventsManager&);
		void operator=(const EventsManager&);

};

#endif
