#ifndef MOUSEPTRCOORDS_H
#define MOUSEPTRCOORDS_H

#include <SFML/Graphics.hpp>

#include "managers/EventsManager.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class MousePtrCoords : public TIEntity {
	public:
		MousePtrCoords();
		~MousePtrCoords() {};

		void initialize();
		void update(const float);

	private:

		sf::Vector2f cachedMouseWorldPostion = sf::Vector2f(0, 0);
		sf::Vector2f cachedMouseWindowPostion = sf::Vector2f(0, 0);
		EventsManager* eventsManager = EventsManager::Instance();
};

}
#endif
