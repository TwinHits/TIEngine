#include "utils/StringHelpers.h"

#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <stdexcept>

#include <SFML/Graphics.hpp>

#include "managers/LogManager.h"
#include "objects/enumeration/Language.h"


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


sf::Event::EventType TIE::String::stringToEvent(std::string& event) {
    TIE::String::toUpper(event);
    if (event == "TEXTENTERED") { return sf::Event::TextEntered; }
    else if (event == "KEYPRESSED") { return sf::Event::KeyPressed; }
    else if (event == "KEYRELEASED") { return sf::Event::KeyReleased; }
    else if (event == "MOUSEWHEELMOVED") { return sf::Event::MouseWheelMoved; }
    else if (event == "MOUSEWHEELSCROLLED") { return sf::Event::MouseWheelScrolled; }
    else if (event == "MOUSEBUTTONPRESSED") { return sf::Event::MouseButtonPressed; }
    else if (event == "MOUSEBUTTONRELEASED") { return sf::Event::MouseButtonReleased; }
    else if (event == "MOUSEMOVED") { return sf::Event::MouseMoved; }
	return sf::Event::Count;
}

sf::Keyboard::Key TIE::String::stringToKey(std::string& key) {
    TIE::String::toUpper(key);
    if (key == "A") { return sf::Keyboard::A; }
    else if (key == "B") { return sf::Keyboard::B; }
    else if (key == "C") { return sf::Keyboard::C; }
    else if (key == "D") { return sf::Keyboard::D; }
    else if (key == "E") { return sf::Keyboard::E; }
    else if (key == "F") { return sf::Keyboard::F; }
    else if (key == "G") { return sf::Keyboard::G; }
    else if (key == "H") { return sf::Keyboard::H; }
    else if (key == "I") { return sf::Keyboard::I; }
    else if (key == "J") { return sf::Keyboard::J; }
    else if (key == "K") { return sf::Keyboard::K; }
    else if (key == "L") { return sf::Keyboard::L; }
    else if (key == "M") { return sf::Keyboard::M; }
    else if (key == "N") { return sf::Keyboard::N; }
    else if (key == "O") { return sf::Keyboard::O; }
    else if (key == "P") { return sf::Keyboard::P; }
    else if (key == "Q") { return sf::Keyboard::Q; }
    else if (key == "R") { return sf::Keyboard::R; }
    else if (key == "S") { return sf::Keyboard::S; }
    else if (key == "T") { return sf::Keyboard::T; }
    else if (key == "U") { return sf::Keyboard::U; }
    else if (key == "V") { return sf::Keyboard::V; }
    else if (key == "W") { return sf::Keyboard::W; }
    else if (key == "X") { return sf::Keyboard::X; }
    else if (key == "Y") { return sf::Keyboard::Y; }
    else if (key == "Z") { return sf::Keyboard::Z; }
    else if (key == "NUM0") { return sf::Keyboard::Num0; }
    else if (key == "NUM1") { return sf::Keyboard::Num1; }
    else if (key == "NUM2") { return sf::Keyboard::Num2; }
    else if (key == "NUM3") { return sf::Keyboard::Num3; }
    else if (key == "NUM4") { return sf::Keyboard::Num4; }
    else if (key == "NUM5") { return sf::Keyboard::Num5; }
    else if (key == "NUM6") { return sf::Keyboard::Num6; }
    else if (key == "NUM7") { return sf::Keyboard::Num7; }
    else if (key == "NUM8") { return sf::Keyboard::Num8; }
    else if (key == "NUM9") { return sf::Keyboard::Num9; }
    else if (key == "ESCAPE") { return sf::Keyboard::Escape; }
    else if (key == "LCONTROL") { return sf::Keyboard::LControl; }
    else if (key == "LSHIFT") { return sf::Keyboard::LShift; }
    else if (key == "LALT") { return sf::Keyboard::LAlt; }
    else if (key == "LSYSTEM") { return sf::Keyboard::LSystem; }
    else if (key == "RCONTROL") { return sf::Keyboard::RControl; }
    else if (key == "RSHIFT") { return sf::Keyboard::RShift; }
    else if (key == "RALT") { return sf::Keyboard::RAlt; }
    else if (key == "RSYSTEM") { return sf::Keyboard::RSystem; }
    else if (key == "MENU") { return sf::Keyboard::Menu; }
    else if (key == "LBRACKET") { return sf::Keyboard::LBracket; }
    else if (key == "RBRACKET") { return sf::Keyboard::RBracket; }
    else if (key == "SEMICOLON") { return sf::Keyboard::SemiColon; }
    else if (key == "COMMA") { return sf::Keyboard::Comma; }
    else if (key == "PERIOD") { return sf::Keyboard::Period; }
    else if (key == "QUOTE") { return sf::Keyboard::Quote; }
    else if (key == "SLASH") { return sf::Keyboard::Slash; }
    else if (key == "BACKSLASH") { return sf::Keyboard::BackSlash; }
    else if (key == "TILDE") { return sf::Keyboard::Tilde; }
    else if (key == "EQUAL") { return sf::Keyboard::Equal; }
    else if (key == "DASH") { return sf::Keyboard::Dash; }
    else if (key == "SPACE") { return sf::Keyboard::Space; }
    else if (key == "RETURN") { return sf::Keyboard::Return; }
    else if (key == "BACKSPACE") { return sf::Keyboard::BackSpace; }
    else if (key == "TAB") { return sf::Keyboard::Tab; }
    else if (key == "PAGEUP") { return sf::Keyboard::PageUp; }
    else if (key == "PAGEDOWN") { return sf::Keyboard::PageDown; }
    else if (key == "END") { return sf::Keyboard::End; }
    else if (key == "HOME") { return sf::Keyboard::Home; }
    else if (key == "INSERT") { return sf::Keyboard::Insert; }
    else if (key == "DELETE") { return sf::Keyboard::Delete; }
    else if (key == "ADD") { return sf::Keyboard::Add; }
    else if (key == "SUBTRACT") { return sf::Keyboard::Subtract; }
    else if (key == "MULTIPLY") { return sf::Keyboard::Multiply; }
    else if (key == "DIVIDE") { return sf::Keyboard::Divide; }
    else if (key == "LEFT") { return sf::Keyboard::Left; }
    else if (key == "RIGHT") { return sf::Keyboard::Right; }
    else if (key == "UP") { return sf::Keyboard::Up; }
    else if (key == "DOWN") { return sf::Keyboard::Down; }
    else if (key == "NUMPAD0") { return sf::Keyboard::Numpad0; }
    else if (key == "NUMPAD1") { return sf::Keyboard::Numpad1; }
    else if (key == "NUMPAD2") { return sf::Keyboard::Numpad2; }
    else if (key == "NUMPAD3") { return sf::Keyboard::Numpad3; }
    else if (key == "NUMPAD4") { return sf::Keyboard::Numpad4; }
    else if (key == "NUMPAD5") { return sf::Keyboard::Numpad5; }
    else if (key == "NUMPAD6") { return sf::Keyboard::Numpad6; }
    else if (key == "NUMPAD7") { return sf::Keyboard::Numpad7; }
    else if (key == "NUMPAD8") { return sf::Keyboard::Numpad8; }
    else if (key == "NUMPAD9") { return sf::Keyboard::Numpad9; }
    else if (key == "F1") { return sf::Keyboard::F1; }
    else if (key == "F2") { return sf::Keyboard::F2; }
    else if (key == "F3") { return sf::Keyboard::F3; }
    else if (key == "F4") { return sf::Keyboard::F4; }
    else if (key == "F5") { return sf::Keyboard::F5; }
    else if (key == "F6") { return sf::Keyboard::F6; }
    else if (key == "F7") { return sf::Keyboard::F7; }
    else if (key == "F8") { return sf::Keyboard::F8; }
    else if (key == "F9") { return sf::Keyboard::F9; }
    else if (key == "F10") { return sf::Keyboard::F10; }
    else if (key == "F11") { return sf::Keyboard::F11; }
    else if (key == "F12") { return sf::Keyboard::F12; }
    else if (key == "F13") { return sf::Keyboard::F13; }
    else if (key == "F14") { return sf::Keyboard::F14; }
    else if (key == "F15") { return sf::Keyboard::F15; }
    else if (key == "PAUSE") { return sf::Keyboard::Pause; }
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
