#include "utilities/ToRadians.h"

#define _USE_MATH_DEFINES
#include <cmath>

float TIE::ToRadians(float degrees) {
	return (degrees * M_PI) / 180;
}
