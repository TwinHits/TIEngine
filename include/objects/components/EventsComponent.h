#ifndef EVENTSCOMPONENT_H
#define EVENTSCOMPONENT_H

#include "objects/components/Component.h"

#include <string>

namespace TIE {

class EventsComponent : public Component {
	public: 
		EventsComponent() {};
		~EventsComponent() {};

		const std::string& getClick();
		void setClick(const std::string&);

	private:
		std::string click = "";

};

}

#endif
