#define _USE_MATH_DEFINES
#include <cmath>

#include "ToDegrees.h"

float TIE::ToDegrees(double radians)
{
	return (radians *180)/M_PI;
}
