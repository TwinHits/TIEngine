#ifndef HELPERS_H
#define HELPERS_H

#include <string>

#include "../include/TIEngine.h"

//Helper method for making sure that the last line of the debuglog contains the provided text
static bool CheckDebugLogForText(const std::string& text) {
	std::ifstream log;
	log.open(TIE::ConfigManager::Instance()->getDebugLogPath() + "debug.log", std::ios_base::app);
	if (!log.is_open()) {
		throw std::runtime_error("Failed to open debug log file: " + TIE::ConfigManager::Instance()->getDebugLogPath() + "debug.log");
	}
	else {
		std::string line = "";
		std::vector<std::string> lines;
		while (std::getline(log, line)) {
			lines.push_back(line);
		}

		if (lines.empty()) {
			return false;
		}

		const std::string& lastLine = lines.back();
		if (lastLine.find(text, 0) != std::string::npos) {
			log.close();
			return true;
		}
		else {
			log.close();
			return false;
		}
	}
	return false;
}

#endif