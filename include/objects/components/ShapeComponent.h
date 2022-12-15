#ifndef SHAPECOMPONENT_H
#define SHAPECOMPONENT_H

#include "objects/components/Component.h"

#include <SFML/Graphics.hpp>

#include <vector>

namespace TIE {

class ShapeComponent : public Component {
	public:
		ShapeComponent() {};
		virtual ~ShapeComponent() {};

		void setDrawn(bool);
		bool isDrawn() const;

		sf::RectangleShape& addRectangleShape();
		sf::CircleShape& addCircleShape();

		const std::vector<std::unique_ptr<sf::Shape> >& getShapes();
	private:
		bool drawn = true;
		std::vector<std::unique_ptr<sf::Shape> > shapes;
};

};

#endif
