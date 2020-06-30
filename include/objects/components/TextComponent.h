#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include <SFML/Graphics.hpp>

#include "objects/components/Component.h"

namespace TIE {
	class TextComponent : public Component, public sf::Text {
		public:
			TextComponent();
			virtual ~TextComponent() {};

			void setDrawn(bool drawn);
			bool isDrawn() const;
		private:
			bool drawn = false;
	};
}
#endif
