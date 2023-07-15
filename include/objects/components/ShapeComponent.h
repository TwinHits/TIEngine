#ifndef SHAPECOMPONENT_H
#define SHAPECOMPONENT_H

#include "objects/components/Component.h"

#include <SFML/Graphics.hpp>

#include <map>

#include "objects/GlobalId.h"

namespace TIE {

class ShapeComponent : public Component {
	public:
		ShapeComponent() {};
		virtual ~ShapeComponent() {};

		void setDrawn(bool);
		bool isDrawn() const;

        void setRotates(const bool);
        const bool isRotates() const;

		sf::RectangleShape& addRectangleShape();
		sf::RectangleShape& addRectangleShape(const GlobalId);

		sf::CircleShape& addCircleShape();
		sf::CircleShape& addCircleShape(const GlobalId);

		const std::map<GlobalId, std::unique_ptr<sf::Shape> >& getShapes();
		const std::map<GlobalId, std::unique_ptr<sf::Shape> >& getShapes() const;

		sf::Shape* getShape(const GlobalId);
	private:
		bool drawn = true;
		bool rotates = true;
		std::map<GlobalId, std::unique_ptr<sf::Shape> > shapes;
};

};

#endif
