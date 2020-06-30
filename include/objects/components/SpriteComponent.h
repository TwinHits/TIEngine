#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SFML/Graphics.hpp>

#include "Component.h"

namespace TIE {
	class SpriteComponent : public Component, public sf::Sprite {
		public:
			SpriteComponent();
			virtual ~SpriteComponent() {};

			void setDrawn(bool);
			bool isDrawn() const;
		private: 
			bool drawn = false;
	};
}

#endif