#ifndef EVENTSCOMPONENTSYSTEM_H
#define EVENTSCOMPONENTSYSTEM_H

#include "componentSystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <string>

#include "objects/components/EventsComponent.h"
#include "objects/components/structs/EventState.h"
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
		EventsComponent& addComponent(TIEntity&);
		bool removeComponent(TIEntity&);
		const std::string& getName();

		// Helpers
		void addState(TIEntity&, const std::string&);
		bool removeState(TIEntity&, const std::string&);
		EventState* getState(TIEntity&, const std::string&);

		void addSelectedComponent(EventsComponent&);
		void removeSelectedComponent(EventsComponent&);
		void clearSelectedComponents();

		// TIEFactory keys / Name
		const static inline std::string EVENTS = "events";

		// Engine handled events
		const static inline std::string SELECTED = "selected";
		const static inline std::string UNSELECTED = "unselected";
		const static inline std::string HOVER = "hover";
		const static inline std::string NEUTRAL = "neutral";

	private:
		struct Components {
			EventsComponent& eventsComponent;
			TIEntity& tientity;
		};
		std::list<Components> components;

		std::vector<EventsComponent*> cachedSelectedComponents;

		void updateSelectedStates(EventsComponent&, TIEntity&, const sf::Event&);
		void updateHoverStates(EventsComponent&, TIEntity&, const sf::Vector2f& mousePosition);
};

}
#endif