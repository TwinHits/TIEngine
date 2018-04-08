#include <map>
#include <sstream>

#include <boost/filesystem.hpp>

#include "managers/ConfigManager.h"
#include "managers/LogManager.h"

#include "objects/LogLevel.h"

using namespace TIE;

ConfigManager::ConfigManager() {
	loadConfig(this->defaultConfigPath);
}


ConfigManager::~ConfigManager() {
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


const std::string& ConfigManager::getDatabaseConnectionString() {
	return this->databaseConnectionString;
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

		parseConfig(config);

		config.close();
		return true;
	} else {
		return false;
	}
}


void ConfigManager::parseConfig(std::ifstream& config) {
	std::string line;
	std::map<std::string, std::string> databaseConfig;
	while (std::getline(config, line)) {
		std::stringstream fileline(line);
		std::string key;
		std::string value;

		if (std::getline(fileline, key, '=')) {
			std::getline(fileline, value);	

			if (key == "DebugLogPath") { debugLogPath = value; }
			else if (key == "AssetsPath") { assetsPath = value; }
			else if (key == "DebugLogLevel") { debugLogLevel = strToLogLevel(value); }
			else if (key == "DefaultDisplayLanguage") { defaultDisplayLanguage = parseLanguage(value); }
			else if (key == "DatabaseDBName" || key == "DatabaseUser" || key == "DatabasePassword" || key == "DatabaseHostAddr" || key == "DatabasePort") {
				databaseConfig.insert(std::pair<std::string, std::string>(key, value));
			}
		} 
	}
	this->databaseConnectionString = assembleDatabaseConnectionString(databaseConfig);
}

const std::string ConfigManager::assembleDatabaseConnectionString(const std::map<std::string, std::string> databaseConfig) {
	std::stringstream databaseConnectionString;
	databaseConnectionString << "dbname=" << databaseConfig.at("DatabaseDBName") << " ";
	databaseConnectionString << "user=" << databaseConfig.at("DatabaseUser") << " ";
	databaseConnectionString << "password=" << databaseConfig.at("DatabasePassword") << " ";
	databaseConnectionString << "hostaddr=" << databaseConfig.at("DatabaseHostAddr") << " ";
	databaseConnectionString << "port=" << databaseConfig.at("DatabasePort");
	return databaseConnectionString.str();
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