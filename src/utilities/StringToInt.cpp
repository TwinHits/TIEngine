#include <string>
#include <sstream>

#include "utilities/StringToInt.h"

int TIE::StringToInt(std::string& s)
{
	std::stringstream ss(s);
	int num;
	return ss >> num ? num: 0;
}
