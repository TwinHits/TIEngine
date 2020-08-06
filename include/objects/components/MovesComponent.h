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

		void setTargetPosition(const sf::Vector2f&);
		const sf::Vector2f& getTargetPosition() const;

		void setCachedTargetPosition(const sf::Vector2f&);
		const sf::Vector2f& getCachedTargetPosition() const;

	private: 
		sf::Vector2f velocity;
		sf::Vector2f targetPosition;
		sf::Vector2f cachedTargetPosition;
};

}
#endif
