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

class EventsComponentSystem : public Singleton<EventsComponentSystem>, public ComponentSystem {
	public:
		EventsComponentSystem() {};
		void update(const float);
		void addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);
		const std::string& getName();

		// Helpers
		bool addState(TIEntity&, const std::string&);
		bool removeState(TIEntity&, const std::string&);

		const static inline std::string EVENTS = "events";
	private:
		struct Components {
			EventsComponent& eventsComponent;
			MovesComponent& movesComponent;
			PositionComponent& positionComponent;
			SpriteComponent& spriteComponent;
			TIEntity& tientity;
		};
		std::list<Components> components;

		void updateSelectedStates();
};

}
#endif