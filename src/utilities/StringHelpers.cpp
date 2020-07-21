#include "utilities/StringHelpers.h"

#include <algorithm>
#include <map>
#include <sstream>

#include "objects/enumeration/Language.h"

std::vector<std::string>& TIE::String::split(const std::string& string, char delimiter, std::vector<std::string>& out) {
	std::istringstream iss(string);
	std::string item;
	while (std::getline(iss, item, delimiter)) {
		out.push_back(item);
	}
	if (out.empty()) {
		out.push_back(string); //If there is no delmiter, include the whole string
	}
	return out;
}


int TIE::String::stringToInt(std::string& s) {
	std::stringstream ss(s);
	int num;
	return ss >> num ? num : 0;
}


TIE::Language TIE::String::parseLanguageString(const std::string& string) {
	//Take a string and figure out with language it's referring to.

	std::map<std::string, Language> languages;
	languages["en_US"] = en_US;
	languages["es_ES"] = es_ES;
	languages["fe_FR"] = fe_FR;
	languages["de_DE"] = de_DE;
	languages["ja_JP"] = ja_JP;

	TIE::Language l = languages[string];
	if (l == 0) {
		return en_US;
	} else {
		return l;
	}
}


TIE::LogLevel TIE::String::strToLogLevel(std::string& loglevel) {
	std::transform(loglevel.begin(), loglevel.end(), loglevel.begin(), ::toupper);
	if (loglevel == "COMMAND")
		return TIE::LogLevel::COMMAND;
	else if (loglevel == "ERROR")
		return TIE::LogLevel::ERROR;
	else if (loglevel == "WARN")
		return TIE::LogLevel::WARN;
	else if (loglevel == "INFO")
		return TIE::LogLevel::INFO;
	else if (loglevel == "DEBUG")
		return TIE::LogLevel::DEBUG;
	else
		return TIE::LogLevel::ERROR;
}

