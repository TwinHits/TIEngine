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

		void subscribe(const GlobalId, std::function<void(Message&)>);
		bool hasHandlersFor(const GlobalId);
		const std::vector<std::function<void(Message&)>>* getHandlersFor(const GlobalId);

		void subscribe(const GlobalId, const GlobalId);
		bool hasFunctionIdsFor(const GlobalId);
		const std::vector<GlobalId>* getFunctionIdsFor(const GlobalId);

		const GlobalId redirectsTo();
		const GlobalId redirectsFrom();

		EventsComponent() {};
		~EventsComponent() {};

	private:
		std::map<GlobalId, std::vector<std::function<void(Message&)>>> subscriptionToHandlers;
		std::map<GlobalId, std::vector<GlobalId>> subscriptionToFunctionIds;

		GlobalId redirectFromId = 0;
		GlobalId redirectToId = 0;
};

}

#endif
