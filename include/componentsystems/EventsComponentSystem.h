#ifndef EVENTSCOMPONENTSYSTEM_H
#define EVENTSCOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <string>

#include "objects/components/EventsComponent.h"
#include "objects/components/structs/EventState.h"
#include "objects/tientities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"

namespace TIE {

class EventsComponentSystem : public Singleton<EventsComponentSystem>, public OwnsComponent<EventsComponent> {
	public:
		EventsComponentSystem();
		void update(const float);
		EventsComponent& addComponent(const TIEntityFactory&, TIEntity&);
		EventsComponent& addComponent(TIEntity&);
		bool removeComponent(TIEntity&);

		bool setComponentProperty(const std::string&, bool, TIEntity&);
		bool setComponentProperty(const std::string&, float, TIEntity&);
		bool setComponentProperty(const std::string&, const std::string&, TIEntity&);
		sol::object getComponentProperty(const std::string&, TIEntity&);

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

		bool isEntityInAScrollableView(TIEntity&);
		void updateSelectedStates(EventsComponent&, TIEntity&, const sf::Event&);
		void updateHoverStates(EventsComponent&, TIEntity&, const sf::Vector2f& mousePosition);
};

}
#endif