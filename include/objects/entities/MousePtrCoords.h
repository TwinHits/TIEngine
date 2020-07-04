#ifndef MOUSEPTRCOORDS_H
#define MOUSEPTRCOORDS_H

#include "managers/InputManager.h"
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
		InputManager* inputManager = InputManager::Instance();
};

}
#endif
