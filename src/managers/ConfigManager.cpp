#include <map>
#include <sstream>

#include <boost/filesystem.hpp>

#include "managers/ConfigManager.h"

#include "objects/enumeration/LogLevel.h"

#include "utilities/ParseLanguageString.h"

using namespace TIE;

ConfigManager::ConfigManager() {
	this->loadConfig(this->defaultConfigPath);
}


const std::string& ConfigManager::getDebugLogPath() {
	return this->debugLogPath;
}


const std::string& ConfigManager::getAssetsPath() {
	return this->assetsPath;
}


const std::string& ConfigManager::getScriptsPath() {
	return this->scriptsPath;
}


LogLevel ConfigManager::getDebugLogLevel() {
	return this->debugLogLevel;
}


void ConfigManager::setDebugLogLevel(LogLevel debugLogLevel) {
	this->debugLogLevel = debugLogLevel;
}


const Language& ConfigManager::getDefaultDisplayLanguage() {
	return this->defaultDisplayLanguage;
}


const bool ConfigManager::getShowMousePtrCoords() {
	return this->showMousePtrCoords;
}

const bool ConfigManager::getShowDegreeGuide() {
	return this->showDegreeGuide;
}


void ConfigManager::setDefaultDisplayLanguage(const Language& defaultDisplayLanguage) {
	this->defaultDisplayLanguage = defaultDisplayLanguage;
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

		this->parseConfig(config);

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
			else if (key == "AssetsPath") { assetsPath = value; }
			else if (key == "DebugLogLevel") { debugLogLevel = strToLogLevel(value); }
			else if (key == "DefaultDisplayLanguage") { defaultDisplayLanguage = parseLanguageString(value); }
			else if (key == "ShowMousePtrCoords") {
				if (value == "true") {
					this->showMousePtrCoords = true;
				}
			} else if (key == "ShowDegreeGuide") {
				if (value == "true") {
					this->showDegreeGuide = true; 
				}
			}
		} 
	}
}


void ConfigManager::restoreDefaultConfiguration() {
	this->debugLogPath = this->defaultDebugLogPath;
	this->assetsPath = this->defaultAssetsPath;
	this->debugLogLevel = this->defaultDebugLogLevel;
	this->defaultDisplayLanguage = this->defaultDefaultDisplayLanguage;
}
