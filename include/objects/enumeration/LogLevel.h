#ifndef LOGLEVEL_H
#define LOGLEVEL_H

#include <algorithm>
#include <string>

namespace TIE {

enum LogLevel {
	COMMAND, ERROR, WARN, INFO, DEBUG
};

LogLevel strToLogLevel(std::string loglevel);

}
#endif
