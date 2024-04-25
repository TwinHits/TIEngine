#ifndef EVENTSCOMPONENT_H
#define EVENTSCOMPONENT_H

#include "objects/components/Component.h"

#include <functional>
#include <map>
#include <vector>

#include "objects/GlobalId.h"
#include "objects/Message.h"

namespace TIE {

class EventsComponent : public Component {
	public: 
		bool isSubscribedTo(const GlobalId);
		const std::vector<std::function<void(Message&)>>* getHandlersFor(const GlobalId);
		void subscribe(const GlobalId, std::function<void(Message&)>);
		const GlobalId redirectsTo();
		const GlobalId redirectsFrom();

		EventsComponent() {};
		~EventsComponent() {};

	private:
		std::map<GlobalId, std::vector<std::function<void(Message&)>>> subscriptions;
		GlobalId redirectFromId = 0;
		GlobalId redirectToId = 0;
};

}

#endif
