#ifndef MOVESCOMPONENT_H
#define MOVESCOMPONENT_H

#include "objects/components/Component.h"

#include <SFML/Graphics.hpp>

namespace TIE {

class MovesComponent : public Component {
	public:
		MovesComponent() {};
		virtual ~MovesComponent() {};
		
		void setVelocity(sf::Vector2f); //x = speed, y = direction
		const sf::Vector2f getVelocity();

		void setDestination(sf::Vector2f);
		const sf::Vector2f getDestination();

		//If the destintation has changed, then this component's velocity needs to be recalcuated
		bool recalculateVelocity();
	private: 
		sf::Vector2f velocity;
		sf::Vector2f destination;
		sf::Vector2f cachedDesintation;
};

}
#endif
