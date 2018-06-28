#ifndef MOUSEPTRCOORDS_H
#define MOUSEPTRCOORDS_H

#include "managers/InputManager.h"

#include "objects/drawables/TIExt.h"

namespace TIE {

class MousePtrCoords : public TIExt {
	public:
		MousePtrCoords();
		~MousePtrCoords();

	private:
		void updateSelf(const float);

		const sf::Font& font;
		InputManager* inputManager = InputManager::Instance();
};

}
#endif
