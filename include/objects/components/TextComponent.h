#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include <SFML/Graphics.hpp>

#include "objects/components/Component.h"

namespace TIE {

class TextComponent : public Component, public sf::Text {
	public:
		TextComponent();
		virtual ~TextComponent() {};

		void setOffset(const sf::Vector2f&);
		sf::Vector2f& getOffset();

		void setDrawn(bool drawn);
		bool isDrawn() const;
	private:
		sf::Vector2f offset = sf::Vector2f(0, 0);
		bool drawn = false;
};

}
#endif
