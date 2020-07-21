#ifndef STRINGHELPERS_H
#define STRINGHELPERS_H

#include <string>
#include <vector>

#include "objects/enumeration/Language.h"
#include "objects/enumeration/LogLevel.h"

namespace TIE {
	namespace String {
		std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);
		int stringToInt(std::string&);
		Language parseLanguageString(const std::string&);
		LogLevel strToLogLevel(std::string&);
	}
}

#endif
