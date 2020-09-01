#ifndef EVENTSCOMPONENTSYSTEM_H
#define EVENTSCOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <string>

#include "objects/components/EventsComponent.h"
#include "objects/components/MovesComponent.h"
#include "objects/components/PositionComponent.h"
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

		const static std::string EVENTS;
	private:
		struct Components {
			EventsComponent& eventsComponent;
			MovesComponent& movesComponent;
			PositionComponent& positionComponent;
			SpriteComponent& spriteComponent;
			TIEntity& tientity;
		};
		std::vector<Components> components;

		void updateSelectedStates();
};

}
#endif