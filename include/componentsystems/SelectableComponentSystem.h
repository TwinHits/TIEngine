#ifndef SELECTABLECOMPONENTSYSTEM_H
#define SELECTABLECOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <string>

#include "objects/components/SelectableComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/EventsManager.h"

namespace TIE {

class SelectableComponentSystem : public Singleton<SelectableComponentSystem>, ComponentSystem {
	public:
		SelectableComponentSystem() {};
		void update(TIEntity&, const float);

		SelectableComponent* addComponent(const TIEntityFactory&, TIEntity&);

		bool isSelected(TIEntity&);

		static const std::string SELECTABLE;
		static const std::string SELECTABLE_KEY;
	private:
		EventsManager* eventsManager = EventsManager::Instance();
};

}
#endif
