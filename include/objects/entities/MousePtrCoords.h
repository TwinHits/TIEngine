#ifndef MOUSEPTRCOORDS_H
#define MOUSEPTRCOORDS_H

#include "managers/EventsManager.h"
#include "objects/entities/TIEntity.h"

namespace TIE {

class MousePtrCoords : public TIEntity {
	public:
		MousePtrCoords();
		~MousePtrCoords() {};

		void initialize();
		void update(const float);

	private:

		const sf::Font& font;
		EventsManager* eventsManager = EventsManager::Instance();
};

}
#endif
