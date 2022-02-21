#ifndef MOVESCOMPONENT_H
#define MOVESCOMPONENT_H

#include "objects/components/Component.h"

#include <SFML/Graphics.hpp>

namespace TIE {

class MovesComponent : public Component {
	public:
		MovesComponent() {};
		virtual ~MovesComponent() {};

		float maxSpeed = 0.0f;
		float acceleration = 0.0f;
		float speed = 0.0f;

		bool rotates = true;
		sf::Vector2f rotationalVelocity = sf::Vector2f(0, 0);

		bool hasTargetPosition = false;
		sf::Vector2f targetPosition = sf::Vector2f(0, 0);
		float targetRotation = 0.0f;

		float lastDistanceToTarget = 0.0f;
};

}
#endif
