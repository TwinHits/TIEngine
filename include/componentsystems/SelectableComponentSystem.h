#ifndef SELECTABLECOMPONENTSYSTEM_H
#define SELECTABLECOMPONENTSYSTEM_H

#include "ComponentSystem.h"

#include <string>

#include "objects/components/SelectableComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/EventsManager.h"

namespace TIE {

class SelectableComponentSystem : public ComponentSystem {
	public:
		SelectableComponentSystem() {};
		void update(TIEntity&, const float);

		static SelectableComponent* addSelectableComponent(const TIEntityFactory&, TIEntity&);

		static bool isSelected(TIEntity&);

		static const std::string SELECTABLE;
		static const std::string SELECTABLE_KEY;
	private:
		EventsManager* eventsManager = EventsManager::Instance();
};

}
#endif
