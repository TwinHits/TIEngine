#include "utils/TIEMath.h"

#include "managers/LogManager.h"
#include "utils/constants/TIEMathConstants.h"

float TIE::Math::toRadians(float degrees) { 
	return (degrees * M_PI) / 180; 
}


//Takes a double to supress a warning
float TIE::Math::toDegrees(double radians) { 
	return fmod((radians * 180) / M_PI + 360.0f, 360.0f);
}

float TIE::Math::normalizeAngleDegrees(float angle) {
	// take any number and convert it to 0-359 degrees
	angle = fmod(angle, 360);
	if (angle < 0) {
		angle += 360;
	}
	return angle;
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
	return fabs(f1 - f2) <= TIE::TIEMathConstants::FLOAT_COMPARISION_EPSILION;
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


const sf::Vector2f TIE::Math::rotateVectorByAngle(const sf::Vector2f& vector, const float degrees) {
	// https://www.reddit.com/r/sfml/comments/sv3z8d/how_to_orient_child_sprite_position_and_rotation/
    float radians = TIE::Math::toRadians(degrees);
	return sf::Vector2f(vector.x * cos(radians) - vector.y * sin(radians), vector.x * sin(radians) + vector.y * cos(radians));
}


bool TIE::Math::doLinesIntersect(sf::VertexArray line1, sf::VertexArray line2) {
	// https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
	// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines 
	// intersect the intersection point may be stored in the floats i_x and i_y.
	float p0_x = line1[0].position.x;
	float p0_y = line1[0].position.y;

	float p1_x = line1[1].position.x;
	float p1_y = line1[1].position.y;

	float p2_x = line2[0].position.x;
	float p2_y = line2[0].position.y;

	float p3_x = line2[1].position.x;
	float p3_y = line2[1].position.y;

    float s1_x = p1_x - p0_x;     
    float s1_y = p1_y - p0_y;
    float s2_x = p3_x - p2_x;     
    float s2_y = p3_y - p2_y;

    float s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    float t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    return s >= 0 && s <= 1 && t >= 0 && t <= 1;
}


bool TIE::Math::doesLineIntersectRect(sf::VertexArray line, sf::FloatRect rect) {
	sf::VertexArray top_edge = sf::VertexArray();
	top_edge.append(sf::Vertex(sf::Vector2f(rect.top, rect.left)));
	top_edge.append(sf::Vertex(sf::Vector2f(rect.top, rect.left + rect.width)));
	if (TIE::Math::doLinesIntersect(line, top_edge)) {
		return true;
	}

	sf::VertexArray left_edge = sf::VertexArray();
	left_edge.append(sf::Vertex(sf::Vector2f(rect.top, rect.left)));
	left_edge.append(sf::Vertex(sf::Vector2f(rect.top + rect.height, rect.left)));
	if (TIE::Math::doLinesIntersect(line, left_edge)) {
		return true;
	}

	sf::VertexArray bottom_edge = sf::VertexArray();
	bottom_edge.append(sf::Vertex(sf::Vector2f(rect.top + rect.height, rect.left)));
	bottom_edge.append(sf::Vertex(sf::Vector2f(rect.top + rect.height, rect.left + rect.width)));
	if (TIE::Math::doLinesIntersect(line, bottom_edge)) {
		return true;
	}

	sf::VertexArray right_edge = sf::VertexArray();
	right_edge.append(sf::Vertex(sf::Vector2f(rect.top, rect.left + rect.width)));
	right_edge.append(sf::Vertex(sf::Vector2f(rect.top + rect.height, rect.left + rect.width)));
	if (TIE::Math::doLinesIntersect(line, right_edge)) {
		return true;
	}

	return false;
}

bool TIE::Math::isNice(int number) {
	return number == 69;
}

