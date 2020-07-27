#include <map>
#include <sstream>

#include "managers/ConfigManager.h"

#include <boost/filesystem.hpp>

#include "managers/ScriptManager.h"
#include "objects/enumeration/LogLevel.h"
#include "utilities/StringHelpers.h"

using namespace TIE;

bool ConfigManager::initialize() {
	this->loadConfig(this->defaultConfigPath);
	return true;
}


const std::string& ConfigManager::getDebugLogPath() {
	return this->debugLogPath;
}


const std::string& ConfigManager::getAssetsPath() {
	return this->assetsPath;
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

const std::string& TIE::ConfigManager::getStartUpScript() {
	return this->startUpScript;
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
			else if (key == "DebugLogLevel") { debugLogLevel = String::strToLogLevel(value); }
			else if (key == "DefaultDisplayLanguage") { defaultDisplayLanguage = String::parseLanguageString(value); }
			else if (key == "ShowMousePtrCoords") {
				if (value == "true") {
					this->showMousePtrCoords = true;
				}
			} else if (key == "ShowDegreeGuide") {
				if (value == "true") {
					this->showDegreeGuide = true; 
				}
			} else if (key == "StartUpScript") {
				this->startUpScript = value;
			}
		}	 
	}
}


void ConfigManager::restoreDefaultConfiguration() {
	this->debugLogPath = this->defaultDebugLogPath;
	this->assetsPath = this->defaultAssetsPath;
	this->debugLogLevel = this->defaultDebugLogLevel;
	this->defaultDisplayLanguage = this->defaultDefaultDisplayLanguage;
	this->showDegreeGuide = this->defaultShowDegreeGuide;
	this->showMousePtrCoords = this->showMousePtrCoords;
	this->startUpScript = this->defaultStartUpScript;
}
