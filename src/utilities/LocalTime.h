#ifndef LOCALTIME_H
#define LOCALTIME_H

#include <ctime>
#include <string>

std::string LocalTime()
{
	auto t = std::time(nullptr);
	auto local = std::localtime(&t);

	char buffer[30];
	std::strftime(buffer, 30,"%c", local);

	return std::string(buffer);
}

#endif
