#include "utils/TIEMath.h"

#include "managers/LogManager.h"

float TIE::Math::toRadians(float degrees) { 
	return (degrees * M_PI) / 180; 
}


//Takes a double to supress a warning
float TIE::Math::toDegrees(double radians) { 
	return fmod((radians * 180) / M_PI + 360.0f, 360.0f);
}


float TIE::Math::distanceBetweenTwoPoints(const sf::Vector2f& p1, const sf::Vector2f& p2) {
	return fabsf(std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2)));
}


float TIE::Math::distanceBetweenTwoAngles(const float f1, const float f2) {
	float diff = fmod(f2 - f1 + 180, 360) - 180;
	return fabsf(diff < -180 ? diff + 360 : diff);
}


float TIE::Math::angleBetweenTwoPoints(const sf::Vector2f& p1, const sf::Vector2f& p2) {
	return TIE::Math::toDegrees(std::atan2(p2.y - p1.y, p2.x - p1.x));
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


const bool TIE::Math::areVectorsEqual(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return TIE::Math::areFloatsEqual(v1.x, v2.x) && TIE::Math::areFloatsEqual(v1.y, v2.y);
}


const bool TIE::Math::isAngleBetweenAngles(const float angle, const float left, const float right) {
	const float difference = TIE::Math::distanceBetweenTwoAngles(left, right);
	const float leftDistance = TIE::Math::distanceBetweenTwoAngles(angle, left);
	const float rightDistance = TIE::Math::distanceBetweenTwoAngles(angle, right);
	return leftDistance <= difference && rightDistance <= difference;
}


const bool TIE::Math::isVectorBetweenVectors(const sf::Vector2f& endA, const sf::Vector2f& endB, const sf::Vector2f& mid) {
	return TIE::Math::areFloatsEqual(TIE::Math::distanceBetweenTwoPoints(endA, mid) + TIE::Math::distanceBetweenTwoPoints(endB, mid), TIE::Math::distanceBetweenTwoPoints(endA, endB));
}


const float TIE::Math::getDotProduct(const sf::Vector2f& a, const sf::Vector2f& b) {
	return a.x * b.x + a.y * b.y;
}


const sf::Vector2f TIE::Math::getProjectedVector(const sf::Vector2f& project, const sf::Vector2f& onto) {
	float d = TIE::Math::getDotProduct(onto, onto);
    if (d > 0) {
		float dp = TIE::Math::getDotProduct(project, onto);
		return onto * (dp / d);
    }
	return onto;
}


bool TIE::Math::isNice(int number) {
	return number == 69;
}

