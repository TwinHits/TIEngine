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

			void setRotates(bool);
			bool isRotates() const;

			void setConstrainProportions(bool);
			bool isConstrainProportions() const;

			const sf::Sprite& getSprite();

			const sf::Vector2f getScaledSize();

			bool isCenterOrigin();
		private: 
			bool drawn = true;
			bool rotates = true;
			bool constrainProportions = true;
	};
}

#endif