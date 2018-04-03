#include <map>
#include <sstream>

#include <boost/filesystem.hpp>

#include "managers/ConfigManager.h"
#include "managers/LogManager.h"

#include "utilities/StringToInt.h"

using namespace TIE;

ConfigManager::ConfigManager() {
	loadConfig(this->defaultConfigPath);
}


ConfigManager::~ConfigManager() {
}


const std::string& ConfigManager::getDebugLogPath() {
	return debugLogPath;
}


const std::string& ConfigManager::getAssetsPath() {
	return assetsPath;
}


const int& ConfigManager::getDebugLogLevel() {
	return debugLogLevel;
}


const Language& ConfigManager::getDefaultDisplayLanguage() {
	return defaultDisplayLanguage;
}


bool TIE::ConfigManager::loadConfigFile(const std::string& path) {
	return loadConfig(path);
}


bool ConfigManager::loadConfig(const std::string& path) {
	auto configPath = boost::filesystem::path(path);
	if (exists(configPath)) { 
		std::ifstream config;

		config.open(configPath.string());
		if (!config.is_open()) {
			throw std::runtime_error("File '" + configPath.string() + "' was found, but did not open. Cannot parse configuration values so using default values.");
		}	

		parseConfig(config);

		config.close();
		return true;
	} else {
		return false;
	}
}


void ConfigManager::parseConfig(std::ifstream& config) {
	std::string line;
	while (std::getline(config, line)) {
		std::stringstream fileline(line);
		std::string key;
		std::string value;

		if (std::getline(fileline, key, '=')) {
			std::getline(fileline, value);	

			if (key == "DebugLogPath") { debugLogPath = value; }
			if (key == "AssetsPath") { assetsPath = value; }
			if (key == "DebugLogLevel") { debugLogLevel = StringToInt(value); }
			if (key == "DefaultDisplayLanguage") { defaultDisplayLanguage = parseLanguage(value); }
		}
	}
}


Language ConfigManager::parseLanguage(const std::string& s) {
	//defaultDisplayLanguage is stored as a string in the config.ini, and must
	//be converted to it's enumerated type.
	std::map<std::string, Language> languages;
	languages["en_US"] = en_US;
	languages["es_ES"] = es_ES;
	languages["fe_FR"] = fe_FR;
	languages["de_DE"] = de_DE;
	languages["ja_JP"] = ja_JP;

	Language l = languages[s];
	if (l == 0) {
		return en_US;
	} else {
		return l;
	}
}