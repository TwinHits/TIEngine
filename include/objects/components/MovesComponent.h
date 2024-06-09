#ifndef MOVESCOMPONENT_H
#define MOVESCOMPONENT_H

#include "objects/components/Component.h"

#include <queue>

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

		std::queue<sf::Vector2f> path;

		float targetRotation = 0.0f;

		float targetSpeed = 0.0f;
		float targetRotationalSpeed = 0.0f;

		float lastDistanceToTarget = 0.0f;
		float lastRotationDistanceToTarget = 0.0f;

		const bool hasTargetPosition() {
			return this->path.size();
		};

		const sf::Vector2f& getTargetPosition() {
			return this->path.front();
		};
};

}
#endif
