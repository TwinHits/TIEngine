#ifndef GRIDGUIDE_H
#define GRIDGUIDE_H

#include "objects/entities/TIEntity.h"

#include <SFML/Graphics.hpp>

namespace TIE {

class GridGuide : public TIEntity {
	public:
		bool initialize(const sf::Vector2f&, const sf::Vector2i&, const sf::Vector2f&);
		void update(const float);

		GridGuide() {};
		~GridGuide() {};
	private:

};

}

#endif
