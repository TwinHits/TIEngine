#include <algorithm>
#include <string>

#include "objects/LogLevel.h"

TIE::LogLevel TIE::strToLogLevel(std::string loglevel) {
	std::transform(loglevel.begin(), loglevel.end(), loglevel.begin(), ::toupper);
	if (loglevel == "COMMAND")
		return TIE::LogLevel::COMMAND;
	else if (loglevel == "ERROR")
		return TIE::LogLevel::ERROR;
	else if (loglevel == "WARN")
		return TIE::LogLevel::WARN;
	else if (loglevel == "INFO")
		return TIE::LogLevel::INFO;
	else
		throw std::runtime_error("This is not a known loglevel: " + loglevel);
}