#include "utilities/StringHelpers.h"

#include <algorithm>
#include <map>
#include <sstream>

#include <SFML/Graphics.hpp>

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
    if (event == "TextEntered") { return sf::Event::TextEntered; }
    else if (event == "KeyPressed") { return sf::Event::KeyPressed; }
    else if (event == "KeyReleased") { return sf::Event::KeyReleased; }
    else if (event == "MouseWheelMoved") { return sf::Event::MouseWheelMoved; }
    else if (event == "MouseWheelScrolled") { return sf::Event::MouseWheelScrolled; }
    else if (event == "MouseButtonPressed") { return sf::Event::MouseButtonPressed; }
    else if (event == "MouseButtonReleased") { return sf::Event::MouseButtonReleased; }
    else if (event == "MouseMoved") { return sf::Event::MouseMoved; }
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
    else if (key == "Num0") { return sf::Keyboard::Num0; }
    else if (key == "Num1") { return sf::Keyboard::Num1; }
    else if (key == "Num2") { return sf::Keyboard::Num2; }
    else if (key == "Num3") { return sf::Keyboard::Num3; }
    else if (key == "Num4") { return sf::Keyboard::Num4; }
    else if (key == "Num5") { return sf::Keyboard::Num5; }
    else if (key == "Num6") { return sf::Keyboard::Num6; }
    else if (key == "Num7") { return sf::Keyboard::Num7; }
    else if (key == "Num8") { return sf::Keyboard::Num8; }
    else if (key == "Num9") { return sf::Keyboard::Num9; }
    else if (key == "Escape") { return sf::Keyboard::Escape; }
    else if (key == "LControl") { return sf::Keyboard::LControl; }
    else if (key == "LShift") { return sf::Keyboard::LShift; }
    else if (key == "LAlt") { return sf::Keyboard::LAlt; }
    else if (key == "LSystem") { return sf::Keyboard::LSystem; }
    else if (key == "RControl") { return sf::Keyboard::RControl; }
    else if (key == "RShift") { return sf::Keyboard::RShift; }
    else if (key == "RAlt") { return sf::Keyboard::RAlt; }
    else if (key == "RSystem") { return sf::Keyboard::RSystem; }
    else if (key == "Menu") { return sf::Keyboard::Menu; }
    else if (key == "LBracket") { return sf::Keyboard::LBracket; }
    else if (key == "RBracket") { return sf::Keyboard::RBracket; }
    else if (key == "SemiColon") { return sf::Keyboard::SemiColon; }
    else if (key == "Comma") { return sf::Keyboard::Comma; }
    else if (key == "Period") { return sf::Keyboard::Period; }
    else if (key == "Quote") { return sf::Keyboard::Quote; }
    else if (key == "Slash") { return sf::Keyboard::Slash; }
    else if (key == "BackSlash") { return sf::Keyboard::BackSlash; }
    else if (key == "Tilde") { return sf::Keyboard::Tilde; }
    else if (key == "Equal") { return sf::Keyboard::Equal; }
    else if (key == "Dash") { return sf::Keyboard::Dash; }
    else if (key == "Space") { return sf::Keyboard::Space; }
    else if (key == "Return") { return sf::Keyboard::Return; }
    else if (key == "BackSpace") { return sf::Keyboard::BackSpace; }
    else if (key == "Tab") { return sf::Keyboard::Tab; }
    else if (key == "PageUp") { return sf::Keyboard::PageUp; }
    else if (key == "PageDown") { return sf::Keyboard::PageDown; }
    else if (key == "End") { return sf::Keyboard::End; }
    else if (key == "Home") { return sf::Keyboard::Home; }
    else if (key == "Insert") { return sf::Keyboard::Insert; }
    else if (key == "Delete") { return sf::Keyboard::Delete; }
    else if (key == "Add") { return sf::Keyboard::Add; }
    else if (key == "Subtract") { return sf::Keyboard::Subtract; }
    else if (key == "Multiply") { return sf::Keyboard::Multiply; }
    else if (key == "Divide") { return sf::Keyboard::Divide; }
    else if (key == "Left") { return sf::Keyboard::Left; }
    else if (key == "Right") { return sf::Keyboard::Right; }
    else if (key == "Up") { return sf::Keyboard::Up; }
    else if (key == "Down") { return sf::Keyboard::Down; }
    else if (key == "Numpad0") { return sf::Keyboard::Numpad0; }
    else if (key == "Numpad1") { return sf::Keyboard::Numpad1; }
    else if (key == "Numpad2") { return sf::Keyboard::Numpad2; }
    else if (key == "Numpad3") { return sf::Keyboard::Numpad3; }
    else if (key == "Numpad4") { return sf::Keyboard::Numpad4; }
    else if (key == "Numpad5") { return sf::Keyboard::Numpad5; }
    else if (key == "Numpad6") { return sf::Keyboard::Numpad6; }
    else if (key == "Numpad7") { return sf::Keyboard::Numpad7; }
    else if (key == "Numpad8") { return sf::Keyboard::Numpad8; }
    else if (key == "Numpad9") { return sf::Keyboard::Numpad9; }
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
    else if (key == "Pause") { return sf::Keyboard::Pause; }
    return sf::Keyboard::Unknown;
}

