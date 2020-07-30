#ifndef EVENTSCOMPONENTSYSTEM_H
#define EVENTSCOMPONENTSYSTEM_H

#include "ComponentSystem.h"

#include <string>

#include "objects/components/EventsComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/EventsManager.h"
#include "managers/GridManager.h"

namespace TIE {

class EventsComponentSystem : public ComponentSystem {
	public:
		EventsComponentSystem() {};
		void update(TIEntity&, const float);

		static EventsComponent* addEventsComponent(const TIEntityFactory&, TIEntity&);

		static const std::string EVENTS;
		static const std::string SELECTED;
	private:
		std::vector<std::string>& getStates(TIEntity&, std::vector<std::string>&);

		EventsManager* eventsManager = EventsManager::Instance();
		GridManager* gridManager = GridManager::Instance();
};

}
#endif