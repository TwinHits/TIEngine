#ifndef LINECOMPONENT_H
#define LINECOMPONENT_H

#include <SFML/Graphics.hpp>

#include "objects/components/Component.h"

namespace TIE {

class LineComponent : public Component {
	public:
		LineComponent() {};
		virtual ~LineComponent() {};

		void setMagnitude(const float);
		const float getMagnitude();
		const float getMagnitude() const;

		void setLine(const sf::VertexArray&);
		const sf::VertexArray& getLine();
		const sf::VertexArray& getLine() const;

	private:
		float magnitude = 0;
		sf::VertexArray line = sf::VertexArray(sf::Lines, 2);
};

}
#endif
