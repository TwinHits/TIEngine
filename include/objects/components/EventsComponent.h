#ifndef EVENTSCOMPONENT_H
#define EVENTSCOMPONENT_H

#include "objects/components/Component.h"

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

namespace TIE {

class EventsComponent : public Component {
	public: 
		EventsComponent() {};
		~EventsComponent() {};

		bool hasHandlers();

		const std::string* getEventHandler(const std::string&, const sf::Event&);

		void setEventHandler(const std::string&, const sf::Event::EventType&, const std::string&);
		const std::string* getEventHandler(const std::string&, const sf::Event::EventType&);
		bool hasEventHandlers();

		void setKeyHandler(const std::string&, const sf::Keyboard::Key&, const std::string&);
		const std::string* getKeyHandler(const std::string&, const sf::Keyboard::Key&);
		bool hasKeyHandlers();

	private:
		std::map<std::string, std::map<sf::Event::EventType, std::string> > eventHandlers;
		std::map<std::string, std::map<sf::Keyboard::Key, std::string> > keyHandlers;

};

}

#endif
