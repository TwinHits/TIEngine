#ifndef EVENTSCOMPONENTSYSTEM_H
#define EVENTSCOMPONENTSYSTEM_H

#include "ComponentSystem.h"

#include "objects/entities/TIEntity.h"
#include "managers/EventsManager.h"
#include "managers/GridManager.h"

namespace TIE {

class EventsComponentSystem : public ComponentSystem {
	public:
		EventsComponentSystem() {};
		void update(TIEntity&, const float);

	private:
		EventsManager* eventsManager = EventsManager::Instance();
		GridManager* gridManager = GridManager::Instance();
};

}
#endif