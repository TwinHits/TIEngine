#ifndef MOVESCOMPONENT_H
#define MOVESCOMPONENT_H

#include <SFML/Graphics.hpp>

#include "objects/components/Component.h"

namespace TIE {

class MovesComponent : public Component {
	public:
		MovesComponent();
		virtual ~MovesComponent() {};
		
		void setVelocity(sf::Vector2f); //x = speed, y = direction
		const sf::Vector2f getVelocity();

	private: 
		sf::Vector2f velocity;
};


}
#endif
