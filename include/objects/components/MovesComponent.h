#ifndef MOVESCOMPONENT_H
#define MOVESCOMPONENT_H

#include "objects/components/Component.h"

#include <SFML/Graphics.hpp>

namespace TIE {

class MovesComponent : public Component {
	public:
		MovesComponent() {};
		virtual ~MovesComponent() {};

		float speed = 0.0f;
		float acceleration = 0.0f;
		float deceleration = 0.0f;

		bool rotates = true;
		sf::Vector2f rotationalVelocity = sf::Vector2f(0, 0);
		float rotationalAcceleration = 0.0f;

		sf::Vector2f targetPosition = sf::Vector2f(0, 0);

		float targetRotation = 0.0f;

		float targetSpeed = 0.0f;
		float targetRotationalSpeed = 0.0f;

		float lastDistanceToTarget = 0.0f;
		float lastRotationDistanceToTarget = 0.0f;
};

}
#endif
