#include "utilities/StringToInt.h"

#include <string>
#include <sstream>

int TIE::StringToInt(std::string& s)
{
	std::stringstream ss(s);
	int num;
	return ss >> num ? num: 0;
}
