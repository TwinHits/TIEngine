#ifndef TIEMATH_H
#define TIEMATH_H

#define _USE_MATH_DEFINES
#include <cmath>

#include <SFML/Graphics.hpp>

namespace TIE {
	namespace Math {
		float toRadians(float);
		float toDegrees(double);
		float distanceBetweenTwoPoints(const sf::Vector2f&, const sf::Vector2f&);
		float angleBetweenTwoPoints(const sf::Vector2f&, const sf::Vector2f&);
		sf::Vector2f translateVelocityByTime(const sf::Vector2f&, float);
	}
}

#endif