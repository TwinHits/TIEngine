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
		float distanceBetweenTwoAngles(const float, const float);
		float angleBetweenTwoPoints(const sf::Vector2f&, const sf::Vector2f&);
		sf::Vector2f translateVelocityByTime(const sf::Vector2f&, const float);
		sf::Vector2f normalizePositionToGrid(const sf::Vector2f&, const sf::FloatRect&, const sf::Vector2f&);
		const int directionFromAngleToAngle(const float, const float);
		const bool areFloatsEqual(const float, const float);
		const bool areVectorsEqual(const sf::Vector2f&, const sf::Vector2f&);
		const bool isAngleBetweenAngles(const float, const float, const float);
		const bool isVectorBetweenVectors(const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);
		const float getDotProduct(const sf::Vector2f&, const sf::Vector2f&);
		const sf::Vector2f getProjectedVector(const sf::Vector2f&, const sf::Vector2f&);
		bool isNice(int);
	}
}

#endif