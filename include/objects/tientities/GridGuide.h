#ifndef GRIDGUIDE_H
#define GRIDGUIDE_H

#include "objects/tientities/TIEntity.h"

#include <SFML/Graphics.hpp>

namespace TIE {

class GridGuide : public TIEntity {
	public:
		bool initialize(const sf::FloatRect&, const sf::Vector2i&, const sf::Vector2f&);
		void update(const float);

		GridGuide() {};
		~GridGuide() {};
	private:
		const int GRID_LINE_WIDTH = 2;

};

}

#endif
