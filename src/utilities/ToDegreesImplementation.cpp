#include <cmath>
#define USE_MATH_DEFINES

#include "ToDegrees.h"

float TIE::ToDegrees(double radians)
{
	return (radians *180)/M_PI;
}
