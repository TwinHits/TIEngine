#include <ctime>

#include "utilities/LocalTime.h"

std::string TIE::LocalTime() {
	auto t = std::time(nullptr);
	auto local = std::localtime(&t);

	char buffer[30];
	std::strftime(buffer, 30,"%c", local);

	return std::string(buffer);
}
