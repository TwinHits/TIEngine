#ifndef MOUSEPTRCOORDS_H
#define MOUSEPTRCOORDS_H

#include <SFML/Graphics.hpp>

#include "managers/InputManager.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class MousePtrCoords : public TIEntity {
	public:
		MousePtrCoords();
		~MousePtrCoords() {};

		void update(const float);

	private:

		sf::Vector2f cachedMouseWorldPostion = sf::Vector2f(0, 0);
		sf::Vector2f cachedMouseWindowPostion = sf::Vector2f(0, 0);
		InputManager* inputManager = InputManager::Instance();
};

}
#endif
