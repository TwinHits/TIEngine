#ifndef EVENTSCOMPONENTSYSTEM_H
#define EVENTSCOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <string>

#include "objects/components/EventsComponent.h"
#include "objects/components/MovesComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/EventsManager.h"
#include "managers/WorldManager.h"

namespace TIE {

class EventsComponentSystem : public Singleton<EventsComponentSystem>, ComponentSystem {
	public:
		EventsComponentSystem() {};
		void update(const float);

		void addComponent(const TIEntityFactory&, TIEntity&);

		static const std::string EVENTS;
		static const std::string SELECTED;
		static const std::string SELECTABLE;
		static const std::string SELECTABLE_KEY;
	private:
		struct Components {
			EventsComponent& eventsComponent;
			SpriteComponent& spriteComponent;
			MovesComponent& movesComponent;
			TIEntity& tientity;
		};
		std::vector<Components> components;

		void updateSelectedStates();
};

}
#endif