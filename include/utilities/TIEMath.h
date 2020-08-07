#ifndef TIEMATH_H
#define TIEMATH_H

#define _USE_MATH_DEFINES
#include <cmath>

#include <SFML/Graphics.hpp>

namespace TIE {
	namespace Math {
		float toRadians(const float);
		float toDegrees(const double);
		float distanceBetweenTwoPoints(const sf::Vector2f&, const sf::Vector2f&);
		float angleBetweenTwoPoints(const sf::Vector2f&, const sf::Vector2f&);
		float convertTo360Degrees(const float);
		sf::Vector2f translateVelocityByTime(const sf::Vector2f&, const float);
		sf::Vector2f normalizePositionToGrid(const sf::Vector2f& position, const sf::FloatRect& bounds, const sf::Vector2f& tileSize);
		const int directionFromAngleToAngle(const float, const float);
		bool isNice(int);
	}
}

#endif