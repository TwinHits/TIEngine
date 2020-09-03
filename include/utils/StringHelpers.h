#ifndef STRINGHELPERS_H
#define STRINGHELPERS_H

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "objects/enumeration/Language.h"
#include "objects/enumeration/LogLevel.h"

namespace TIE {
	namespace String {
		std::vector<std::string> slice(const std::string&, const char, const int);
		std::vector<std::string> slice(const std::string&, const char, const int, const int);
		std::vector<std::string>& split(const std::string&, const char, std::vector<std::string>&);
		std::string& toUpper(std::string&);
		int stringToInt(std::string&);
		Language parseLanguageString(const std::string&);
		LogLevel strToLogLevel(std::string&);
		sf::Event::EventType stringToEvent(std::string&);
		sf::Keyboard::Key stringToKey(std::string&);
		sf::IntRect stringToIntRect(const std::string&);
		sf::FloatRect stringToFloatRect(const std::string&);
		sf::Vector2f stringToVector2f(const std::string&);
	}
}

#endif
