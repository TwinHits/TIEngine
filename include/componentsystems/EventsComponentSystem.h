#ifndef EVENTSCOMPONENTSYSTEM_H
#define EVENTSCOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <map>
#include <string>

#include "objects/components/EventsComponent.h"

namespace TIE {

class EventsComponentSystem : public Singleton<EventsComponentSystem>, public OwnsComponent<EventsComponent> {
	public:
		EventsComponentSystem();
		void update(const float);

		EventsComponent& addComponent(const TIEntityFactory&, TIEntity&);
		EventsComponent& addComponent(TIEntity&);
		bool removeComponent(TIEntity&);

		void subscribe(TIEntity&, const GlobalId, std::function<void(Message&)>);
		void subscribe(TIEntity&, const GlobalId, const GlobalId);
		void publish(Message);

		const static inline std::string EVENTS = "events";

	private:
		struct Components {
			EventsComponent& eventsComponent;
			TIEntity& tientity;
		};
		std::list<Components> components;

		std::map<GlobalId, std::vector<Message>> currentFrameEvents;
		std::map<GlobalId, std::vector<Message>> nextFrameEvents;

		Message& setSenderId(Message&);
		Message& setRecipientId(Message&);
};

}
#endif