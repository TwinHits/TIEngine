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
		sf::Vector2f& getVelocity();

		void setTargetPosition(const sf::Vector2f&);
		sf::Vector2f& getTargetPosition();

		void setAngularVelocity(const sf::Vector2f&); //x = speed, y = direction
		sf::Vector2f& getAngularVelocity();

		void setTargetAngle(const float);
		float getTargetAngle();
	private: 
		sf::Vector2f velocity = sf::Vector2f(0, 0);
		sf::Vector2f targetPosition = sf::Vector2f(0, 0);

		sf::Vector2f angularVelocity = sf::Vector2f(0, 0);
		float targetAngle = 0.0f;
};

}
#endif
