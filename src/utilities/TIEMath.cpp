#include "utilities/TIEMath.h"

#include "managers/LogManager.h"

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


float TIE::Math::distanceBetweenTwoAngles(const float f1, const float f2) {
	return fabsf(f1 - f2);
}


float TIE::Math::angleBetweenTwoPoints(const sf::Vector2f& p1, const sf::Vector2f& p2) {
	return TIE::Math::convertTo360Degrees(TIE::Math::toDegrees(std::atan2(p2.y - p1.y, p2.x - p1.x)));
}


float TIE::Math::convertTo360Degrees(const float degrees) {
	return (static_cast<int>(degrees) + 360) % 360;
}


sf::Vector2f TIE::Math::translateVelocityByTime(const sf::Vector2f& velocity, const float time) {
	return sf::Vector2f(std::cos(TIE::Math::toRadians(velocity.y)) * velocity.x * time, std::sin(TIE::Math::toRadians(velocity.y)) * velocity.x * time);
}


sf::Vector2f TIE::Math::normalizePositionToGrid(const sf::Vector2f& position, const sf::FloatRect& bounds, const sf::Vector2f& tileSize) {
	return sf::Vector2f(
		bounds.left + (floor(fabsf(bounds.left - position.x) / tileSize.x) * tileSize.x + tileSize.x / 2),
		bounds.top + (floor(fabsf(bounds.top - position.y) / tileSize.y) * tileSize.y + tileSize.y / 2)
	);
}


const int TIE::Math::directionFromAngleToAngle(const float start, const float end) {
	return fmod(start - end + 360, 360) > 180 ? 1 : -1;
}

const bool TIE::Math::areFloatsEqual(const float f1, const float f2) {
	// https://www.tutorialspoint.com/what-is-the-most-effective-way-for-float-and-double-comparison-in-c-cplusplus
	return fabs(f1 - f2) < std::numeric_limits<float>::epsilon();
}

bool TIE::Math::isNice(int number) {
	return number == 69;
}
