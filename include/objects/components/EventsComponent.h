#ifndef EVENTSCOMPONENT_H
#define EVENTSCOMPONENT_H

#include "objects/components/Component.h"

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

#include "objects/GlobalId.h"
#include "objects/components/structs/EventState.h"

namespace TIE {

class EventsComponent : public Component {
	public: 
		EventsComponent() {};
		~EventsComponent() {};

		bool hasHandlers();

		const GlobalId getEventHandler(const std::string&, const sf::Event&);

		void setEventHandler(const std::string&, const sf::Event::EventType&, const GlobalId);
		const GlobalId getEventHandler(const std::string&, const sf::Event::EventType&);
		bool hasEventHandlers();

		void setKeyHandler(const std::string&, const sf::Keyboard::Key&, const GlobalId);
		const GlobalId getKeyHandler(const std::string&, const sf::Keyboard::Key&);
		bool hasKeyHandlers();

		bool hasState(const std::string&);
		void addState(const std::string&);
		void removeState(const std::string&);
		EventState* getState(const std::string&);
		std::vector<EventState>& getStates();
		
		void setSelectable(bool);
		bool isSelectable();

		void setHoverable(bool);
		bool isHoverable();

	private:
		std::vector<EventState> states;

		// Map of state name to event to Lua function id
		std::map<std::string, std::map<sf::Event::EventType, GlobalId> > eventHandlers;
		std::map<std::string, std::map<sf::Keyboard::Key, GlobalId> > keyHandlers;

		bool selectable = false;
		bool hoverable = false;
};

}

#endif
