#include <map>
#include <sstream>

#include "managers/ConfigManager.h"

#include <boost/filesystem.hpp>

#include "objects/enumeration/LogLevel.h"
#include "utils/StringHelpers.h"

using namespace TIE;

void ConfigManager::initialize() {
	this->loadConfig(this->defaultConfigPath);
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


const std::string& ConfigManager::getStartUpScript() {
	return this->startUpScript;
}


const std::string& ConfigManager::getEngineFontName() {
	return this->engineFontName;
}


const bool ConfigManager::isLuaProfilerEnabled() {
	return this->luaProfilerEnabled;
}


void ConfigManager::setDefaultDisplayLanguage(const Language& defaultDisplayLanguage) {
	this->defaultDisplayLanguage = defaultDisplayLanguage;
}


bool ConfigManager::loadConfigFile(const std::string& path) {
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

			if (key == "DebugLogPath") {
				this->debugLogPath = value;
			} else if (key == "AssetsPath") { 
				this->assetsPath = value; 
			} else if (key == "DebugLogLevel") { 
				this->debugLogLevel = String::strToLogLevel(value); 
			} else if (key == "DefaultDisplayLanguage") { 
				this->defaultDisplayLanguage = String::parseLanguageString(value); 
			} else if (key == "ShowMousePtrCoords") {
				this->showMousePtrCoords = TIE::String::stringToBool(value);
			} else if (key == "ShowDegreeGuide") {
				this->showDegreeGuide = TIE::String::stringToBool(value);
			} else if (key == "StartUpScript") {
				this->startUpScript = value;
			} else if (key == "EngineFontName") {
				this->engineFontName = value;
			} else if (key == "LuaProfilerEnabled") {
				this->luaProfilerEnabled = TIE::String::stringToBool(value);
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
	this->engineFontName = this->defaultEngineFontName;
	this->luaProfilerEnabled = this->defaultLuaProfilerEnabled;
}
