#ifndef MOVESCOMPONENT_H
#define MOVESCOMPONENT_H

#include "objects/components/Component.h"

#include <memory>

#include <SFML/Graphics.hpp>

#include "componentsystems/strategies/Strategy.h"

namespace TIE {

class MovesComponent : public Component {
	public:
		MovesComponent() {};
		virtual ~MovesComponent() {};

		std::unique_ptr<Strategy> movesStrategy = nullptr;

		float speed = 0.0f;
		float acceleration = 0.0f;

		sf::Vector2f rotationalVelocity = sf::Vector2f(0, 0);
		float rotationalAcceleration = 0.0f;

		float targetRotation = 0.0f;

		float targetSpeed = 0.0f;
		float targetRotationalSpeed = 0.0f;
};

}
#endif
