#ifndef GRIDCOMPONENT_H
#define GRIDCOMPONENT_H

#include "objects/components/Component.h"

#include <SFML/Graphics.hpp>

namespace TIE {

class GridComponent : public Component {
	public:

		const sf::Vector2i& getGridSize();
		void setGridSize(const sf::Vector2i&);

		const sf::Vector2f& getTileSize();
		void setTileSize(const sf::Vector2f&);

		GridComponent() {};
		~GridComponent() {};
	private:
		sf::Vector2i gridSize = sf::Vector2i(0, 0);
		sf::Vector2f tileSize = sf::Vector2f(0, 0);
};

}

#endif
