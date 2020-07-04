#include "utilities/ToDegrees.h"

#define _USE_MATH_DEFINES
#include <cmath>

float TIE::ToDegrees(double radians) {
	return (radians *180)/M_PI;
}
