#ifndef STRINGTONUMBER_H
#define STRINGTONUMBER_H

#include <string>
#include <sstream>

int StringToNumber(std::string& s)
{
	std::stringstream ss(s);
	int num;
	return ss >> num ? num: 0;
}

#endif
