#include "utilities/TIEMath.h"

float TIE::Math::toRadians(float degrees) { 
	return (degrees * M_PI) / 180; 
}


//Takes a double to supress a warning
float TIE::Math::toDegrees(double radians) { 
	return (radians * 180) / M_PI; 
}


float TIE::Math::distanceBetweenTwoPoints(const sf::Vector2f& p1, const sf::Vector2f& p2) {
	return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}


float TIE::Math::angleBetweenTwoPoints(const sf::Vector2f& p1, const sf::Vector2f& p2) {
	return TIE::Math::toDegrees(std::atan2(p2.y - p1.y, p2.x - p1.x));
}


sf::Vector2f TIE::Math::translateVelocityByTime(const sf::Vector2f& velocity, float time) {
	return sf::Vector2f(std::cos(TIE::Math::toRadians(velocity.y)) * velocity.x * time, std::sin(TIE::Math::toRadians(velocity.y)) * velocity.x * time);
}
