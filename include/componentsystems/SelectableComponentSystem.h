#ifndef SELECTABLECOMPONENTSYSTEM_H
#define SELECTABLECOMPONENTSYSTEM_H

#include "ComponentSystem.h"

#include "objects/entities/TIEntity.h"
#include "managers/EventsManager.h"

namespace TIE {

class SelectableComponentSystem : public ComponentSystem {
	public:
		SelectableComponentSystem() {};

		void update(TIEntity&, const float);

	private:
		EventsManager* eventsManager = EventsManager::Instance();
};

}
#endif
