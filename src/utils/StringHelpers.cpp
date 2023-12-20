#include "utils/StringHelpers.h"

#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <stdexcept>

#include <SFML/Graphics.hpp>

#include "managers/LogManager.h"
#include "objects/enumeration/Language.h"
#include "objects/enumeration/LogLevel.h"
#include "objects/enumeration/TextAlignment.h"


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


sf::Event::EventType TIE::String::stringToEvent(const std::string& event) {
    std::string uppercasedEvent = std::string(event);
    TIE::String::toUpper(uppercasedEvent);
    if (uppercasedEvent == "TEXTENTERED") { return sf::Event::TextEntered; }
    else if (uppercasedEvent == "KEYPRESSED") { return sf::Event::KeyPressed; }
    else if (uppercasedEvent == "KEYRELEASED") { return sf::Event::KeyReleased; }
    else if (uppercasedEvent == "MOUSEWHEELMOVED") { return sf::Event::MouseWheelMoved; }
    else if (uppercasedEvent == "MOUSEWHEELSCROLLED") { return sf::Event::MouseWheelScrolled; }
    else if (uppercasedEvent == "MOUSEBUTTONPRESSED") { return sf::Event::MouseButtonPressed; }
    else if (uppercasedEvent == "MOUSEBUTTONRELEASED") { return sf::Event::MouseButtonReleased; }
    else if (uppercasedEvent == "MOUSEMOVED") { return sf::Event::MouseMoved; }
	return sf::Event::Count;
}

sf::Keyboard::Key TIE::String::stringToKey(const std::string& key) {
    std::string uppercasedKey = std::string(key);
    TIE::String::toUpper(uppercasedKey);
    if (uppercasedKey == "A") { return sf::Keyboard::A; }
    else if (uppercasedKey == "B") { return sf::Keyboard::B; }
    else if (uppercasedKey == "C") { return sf::Keyboard::C; }
    else if (uppercasedKey == "D") { return sf::Keyboard::D; }
    else if (uppercasedKey == "E") { return sf::Keyboard::E; }
    else if (uppercasedKey == "F") { return sf::Keyboard::F; }
    else if (uppercasedKey == "G") { return sf::Keyboard::G; }
    else if (uppercasedKey == "H") { return sf::Keyboard::H; }
    else if (uppercasedKey == "I") { return sf::Keyboard::I; }
    else if (uppercasedKey == "J") { return sf::Keyboard::J; }
    else if (uppercasedKey == "K") { return sf::Keyboard::K; }
    else if (uppercasedKey == "L") { return sf::Keyboard::L; }
    else if (uppercasedKey == "M") { return sf::Keyboard::M; }
    else if (uppercasedKey == "N") { return sf::Keyboard::N; }
    else if (uppercasedKey == "O") { return sf::Keyboard::O; }
    else if (uppercasedKey == "P") { return sf::Keyboard::P; }
    else if (uppercasedKey == "Q") { return sf::Keyboard::Q; }
    else if (uppercasedKey == "R") { return sf::Keyboard::R; }
    else if (uppercasedKey == "S") { return sf::Keyboard::S; }
    else if (uppercasedKey == "T") { return sf::Keyboard::T; }
    else if (uppercasedKey == "U") { return sf::Keyboard::U; }
    else if (uppercasedKey == "V") { return sf::Keyboard::V; }
    else if (uppercasedKey == "W") { return sf::Keyboard::W; }
    else if (uppercasedKey == "X") { return sf::Keyboard::X; }
    else if (uppercasedKey == "Y") { return sf::Keyboard::Y; }
    else if (uppercasedKey == "Z") { return sf::Keyboard::Z; }
    else if (uppercasedKey == "NUM0") { return sf::Keyboard::Num0; }
    else if (uppercasedKey == "NUM1") { return sf::Keyboard::Num1; }
    else if (uppercasedKey == "NUM2") { return sf::Keyboard::Num2; }
    else if (uppercasedKey == "NUM3") { return sf::Keyboard::Num3; }
    else if (uppercasedKey == "NUM4") { return sf::Keyboard::Num4; }
    else if (uppercasedKey == "NUM5") { return sf::Keyboard::Num5; }
    else if (uppercasedKey == "NUM6") { return sf::Keyboard::Num6; }
    else if (uppercasedKey == "NUM7") { return sf::Keyboard::Num7; }
    else if (uppercasedKey == "NUM8") { return sf::Keyboard::Num8; }
    else if (uppercasedKey == "NUM9") { return sf::Keyboard::Num9; }
    else if (uppercasedKey == "ESCAPE") { return sf::Keyboard::Escape; }
    else if (uppercasedKey == "LCONTROL") { return sf::Keyboard::LControl; }
    else if (uppercasedKey == "LSHIFT") { return sf::Keyboard::LShift; }
    else if (uppercasedKey == "LALT") { return sf::Keyboard::LAlt; }
    else if (uppercasedKey == "LSYSTEM") { return sf::Keyboard::LSystem; }
    else if (uppercasedKey == "RCONTROL") { return sf::Keyboard::RControl; }
    else if (uppercasedKey == "RSHIFT") { return sf::Keyboard::RShift; }
    else if (uppercasedKey == "RALT") { return sf::Keyboard::RAlt; }
    else if (uppercasedKey == "RSYSTEM") { return sf::Keyboard::RSystem; }
    else if (uppercasedKey == "MENU") { return sf::Keyboard::Menu; }
    else if (uppercasedKey == "LBRACKET") { return sf::Keyboard::LBracket; }
    else if (uppercasedKey == "RBRACKET") { return sf::Keyboard::RBracket; }
    else if (uppercasedKey == "SEMICOLON") { return sf::Keyboard::SemiColon; }
    else if (uppercasedKey == "COMMA") { return sf::Keyboard::Comma; }
    else if (uppercasedKey == "PERIOD") { return sf::Keyboard::Period; }
    else if (uppercasedKey == "QUOTE") { return sf::Keyboard::Quote; }
    else if (uppercasedKey == "SLASH") { return sf::Keyboard::Slash; }
    else if (uppercasedKey == "BACKSLASH") { return sf::Keyboard::BackSlash; }
    else if (uppercasedKey == "TILDE") { return sf::Keyboard::Tilde; }
    else if (uppercasedKey == "EQUAL") { return sf::Keyboard::Equal; }
    else if (uppercasedKey == "DASH") { return sf::Keyboard::Dash; }
    else if (uppercasedKey == "SPACE") { return sf::Keyboard::Space; }
    else if (uppercasedKey == "RETURN") { return sf::Keyboard::Return; }
    else if (uppercasedKey == "BACKSPACE") { return sf::Keyboard::BackSpace; }
    else if (uppercasedKey == "TAB") { return sf::Keyboard::Tab; }
    else if (uppercasedKey == "PAGEUP") { return sf::Keyboard::PageUp; }
    else if (uppercasedKey == "PAGEDOWN") { return sf::Keyboard::PageDown; }
    else if (uppercasedKey == "END") { return sf::Keyboard::End; }
    else if (uppercasedKey == "HOME") { return sf::Keyboard::Home; }
    else if (uppercasedKey == "INSERT") { return sf::Keyboard::Insert; }
    else if (uppercasedKey == "DELETE") { return sf::Keyboard::Delete; }
    else if (uppercasedKey == "ADD") { return sf::Keyboard::Add; }
    else if (uppercasedKey == "SUBTRACT") { return sf::Keyboard::Subtract; }
    else if (uppercasedKey == "MULTIPLY") { return sf::Keyboard::Multiply; }
    else if (uppercasedKey == "DIVIDE") { return sf::Keyboard::Divide; }
    else if (uppercasedKey == "LEFT") { return sf::Keyboard::Left; }
    else if (uppercasedKey == "RIGHT") { return sf::Keyboard::Right; }
    else if (uppercasedKey == "UP") { return sf::Keyboard::Up; }
    else if (uppercasedKey == "DOWN") { return sf::Keyboard::Down; }
    else if (uppercasedKey == "NUMPAD0") { return sf::Keyboard::Numpad0; }
    else if (uppercasedKey == "NUMPAD1") { return sf::Keyboard::Numpad1; }
    else if (uppercasedKey == "NUMPAD2") { return sf::Keyboard::Numpad2; }
    else if (uppercasedKey == "NUMPAD3") { return sf::Keyboard::Numpad3; }
    else if (uppercasedKey == "NUMPAD4") { return sf::Keyboard::Numpad4; }
    else if (uppercasedKey == "NUMPAD5") { return sf::Keyboard::Numpad5; }
    else if (uppercasedKey == "NUMPAD6") { return sf::Keyboard::Numpad6; }
    else if (uppercasedKey == "NUMPAD7") { return sf::Keyboard::Numpad7; }
    else if (uppercasedKey == "NUMPAD8") { return sf::Keyboard::Numpad8; }
    else if (uppercasedKey == "NUMPAD9") { return sf::Keyboard::Numpad9; }
    else if (uppercasedKey == "F1") { return sf::Keyboard::F1; }
    else if (uppercasedKey == "F2") { return sf::Keyboard::F2; }
    else if (uppercasedKey == "F3") { return sf::Keyboard::F3; }
    else if (uppercasedKey == "F4") { return sf::Keyboard::F4; }
    else if (uppercasedKey == "F5") { return sf::Keyboard::F5; }
    else if (uppercasedKey == "F6") { return sf::Keyboard::F6; }
    else if (uppercasedKey == "F7") { return sf::Keyboard::F7; }
    else if (uppercasedKey == "F8") { return sf::Keyboard::F8; }
    else if (uppercasedKey == "F9") { return sf::Keyboard::F9; }
    else if (uppercasedKey == "F10") { return sf::Keyboard::F10; }
    else if (uppercasedKey == "F11") { return sf::Keyboard::F11; }
    else if (uppercasedKey == "F12") { return sf::Keyboard::F12; }
    else if (uppercasedKey == "F13") { return sf::Keyboard::F13; }
    else if (uppercasedKey == "F14") { return sf::Keyboard::F14; }
    else if (uppercasedKey == "F15") { return sf::Keyboard::F15; }
    else if (uppercasedKey == "PAUSE") { return sf::Keyboard::Pause; }
    return sf::Keyboard::Unknown;
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
