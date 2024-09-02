#include "utils/String.h"

#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <stdexcept>

#include <SFML/Graphics.hpp>

#include "enumeration/Language.h"
#include "enumeration/LogLevel.h"
#include "enumeration/TextAlignment.h"
#include "managers/LogManager.h"


std::vector<std::string> TIE::String::slice(const std::string& string, const char delimiter, const int start) {
    std::vector<std::string> parts;
    TIE::String::split(string, delimiter, parts);
    if (start < parts.size()) {
        return std::vector<std::string>(parts.begin() + start, parts.end());
    } else {
        return std::vector<std::string>(parts.end(), parts.end());
    }
}

std::vector<std::string> TIE::String::slice(const std::string& string, const char delimiter, const int start, const int end) {
    std::vector<std::string> parts;
    TIE::String::split(string, delimiter, parts);
    if (start < parts.size() && end < parts.size()) {
        return std::vector<std::string>(parts.begin() + start, parts.begin() + end);
    } else if (end < parts.size()) {
        return std::vector<std::string>(parts.begin() + start, parts.end());
    } else {
        return std::vector<std::string>(parts.end(), parts.end());
    }
}


std::vector<std::string>& TIE::String::split(const std::string& string, const char delimiter, std::vector<std::string>& out) {
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


std::string& TIE::String::toUpper(std::string& string) {
	std::transform(string.begin(), string.end(), string.begin(), ::toupper);
    return string;
}


int TIE::String::stringToInt(std::string& s) {
	std::stringstream ss(s);
	int num;
	return ss >> num ? num : 0;
}


bool TIE::String::stringToBool(std::string& s) {
    return s == "true";
}


TIE::Language TIE::String::parseLanguageString(const std::string& string) {
	//Take a string and figure out with language it's referring to.

	std::map<std::string, Language> languages;
	languages["en_US"] = Language::en_US;
    languages["es_ES"] = Language::es_ES;
	languages["fe_FR"] = Language::fe_FR;
    languages["de_DE"] = Language::de_DE;
	languages["ja_JP"] = Language::ja_JP;

	if (languages.count(string)) {
        return languages.at(string);
	} else {
        return Language::en_US;
	}
}


TIE::LogLevel TIE::String::strToLogLevel(std::string& loglevel) {
    TIE::String::toUpper(loglevel);
    if (loglevel == "COMMAND") { return TIE::LogLevel::COMMAND; }
    else if (loglevel == "ERROR") { return TIE::LogLevel::ERROR; } 
    else if (loglevel == "WARN") { return TIE::LogLevel::WARN; }
    else if (loglevel == "INFO") { return TIE::LogLevel::INFO; }
    else if (loglevel == "DEBUG") { return TIE::LogLevel::DEBUG; } 
    else { return TIE::LogLevel::ERROR; }
}


TIE::TextAlignment TIE::String::strToTextAlignment(std::string textAlignment) {
    TIE::String::toUpper(textAlignment);
    if (textAlignment == "TOP_LEFT") { return TIE::TextAlignment::TOP_LEFT; }
    else if (textAlignment == "TOP_CENTER") { return TIE::TextAlignment::TOP_CENTER; }
    else if (textAlignment == "TOP_RIGHT") { return TIE::TextAlignment::TOP_RIGHT; }
    else if (textAlignment == "CENTER_LEFT") { return TIE::TextAlignment::CENTER_LEFT; }
    else if (textAlignment == "CENTER") { return TIE::TextAlignment::CENTER; }
    else if (textAlignment == "CENTER_RIGHT") { return TIE::TextAlignment::CENTER_RIGHT; }
    else if (textAlignment == "BOTTOM_LEFT") { return TIE::TextAlignment::BOTTOM_LEFT; }
    else if (textAlignment == "BOTTOM_CENTER") { return TIE::TextAlignment::BOTTOM_CENTER; }
    else if (textAlignment == "BOTTOM_RIGHT") { return TIE::TextAlignment::BOTTOM_RIGHT; }
    return TIE::TextAlignment::TOP_LEFT;
}


std::string TIE::String::textAlignmentToStr(TIE::TextAlignment textAlignment) {
    if (textAlignment == TIE::TextAlignment::TOP_LEFT) { return "TOP_LEFT"; }
    else if (textAlignment == TIE::TextAlignment::TOP_CENTER) { return "TOP_CENTER"; }
    else if (textAlignment == TIE::TextAlignment::TOP_RIGHT) { return "TOP_RIGHT"; }
    else if (textAlignment == TIE::TextAlignment::CENTER_LEFT) { return "CENTER_LEFT"; }
    else if (textAlignment == TIE::TextAlignment::CENTER) { return "CENTER"; }
    else if (textAlignment == TIE::TextAlignment::CENTER_RIGHT) { return "CENTER_RIGHT"; }
    else if (textAlignment == TIE::TextAlignment::BOTTOM_LEFT) { return "BOTTOM_LEFT"; }
    else if (textAlignment == TIE::TextAlignment::BOTTOM_CENTER) { return "BOTTOM_CENTER"; }
    else if (textAlignment == TIE::TextAlignment::BOTTOM_RIGHT) { return "BOTTOM_RIGHT"; }
    return "";
}


sf::IntRect TIE::String::stringToIntRect(const std::string& string) {
    std::vector<std::string> out;
    TIE::String::split(string, ' ', out);
    float points[4] = { 0 };
    for (int i = 0; i < out.size(); i++) {
        try {
            points[i] = std::stoi(out[i]);
        } catch (const std::invalid_argument& ia) {
            points[i] = 0;
            LogManager::Instance()->warn("Cannot convert " + out[i] + " to a int.");
        }
    }
    return sf::IntRect(points[0], points[1], points[2], points[3]);
}


sf::FloatRect TIE::String::stringToFloatRect(const std::string& string) {
    std::vector<std::string> out;
    TIE::String::split(string, ' ', out);
    float points[4] = { 0 };
    for (int i = 0; i < out.size(); i++) {
        try {
            points[i] = std::stof(out[i]);
        } catch (const std::invalid_argument& ia) {
            points[i] = 0;
            LogManager::Instance()->warn("Cannot convert " + out[i] + " to a float.");
        }
    }
    return sf::FloatRect(points[0], points[1], points[2], points[3]);
}

sf::Vector2f TIE::String::stringToVector2f(const std::string& string) {
    std::vector<std::string> out;
    TIE::String::split(string, ' ', out);
    float points[2] = { 0 };
    for (int i = 0; i < out.size(); i++) {
        try {
            points[i] = std::stof(out[i]);
        } catch (const std::invalid_argument& ia) {
            points[i] = 0;
            LogManager::Instance()->warn("Cannot convert " + out[i] + " to a float.");
        }
    }
    return sf::Vector2f(points[0], points[1]);
}

std::string TIE::String::getDirectoryFromPath(const std::string& scriptPath) {
    std::vector<std::string> parts = String::slice(scriptPath, '/', 0);
    std::string scriptDirectory = "";
    for (auto s = parts.begin(); s != parts.end() - 1; s++) {
        scriptDirectory += *s + "/";
    }
    return scriptDirectory;
}
