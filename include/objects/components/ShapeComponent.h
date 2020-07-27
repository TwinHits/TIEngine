#ifndef SHAPECOMPONENT_H
#define SHAPECOMPONENT_H

#include "objects/components/Component.h"

#include <SFML/Graphics.hpp>

namespace TIE {

class ShapeComponent : public Component, public sf::RectangleShape {
	public:
		ShapeComponent() {};
		virtual ~ShapeComponent() {};

		void setDrawn(bool);
		bool isDrawn() const;
	private:
		bool drawn = false;
};

};

#endif
