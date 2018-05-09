#define _USE_MATH_DEFINES
#include <cmath>

#include "utilities/ToRadians.h"

float TIE::ToRadians(float degrees) {
	return (degrees * M_PI) / 180;
}
