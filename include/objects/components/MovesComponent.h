#ifndef MOVESCOMPONENT_H
#define MOVESCOMPONENT_H

#include "objects/components/Component.h"

#include <SFML/Graphics.hpp>

namespace TIE {

class MovesComponent : public Component {
	public:
		MovesComponent() {};
		virtual ~MovesComponent() {};
		
		void setVelocity(const sf::Vector2f&); //x = speed, y = direction
		const sf::Vector2f& getVelocity();

		void setDestination(const sf::Vector2f&);
		const sf::Vector2f& getDestination() const;

		void setCachedDestination(const sf::Vector2f&);
		const sf::Vector2f& getCachedDestination() const;

	private: 
		sf::Vector2f velocity;
		sf::Vector2f destination;
		sf::Vector2f cachedDesintation;
};

}
#endif
