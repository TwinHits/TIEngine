#include <fstream>
#include <sstream>

#include "../templates/StringToNumber.h"

#include "ConfigManager.h"
#include "LogManager.h"

ConfigManager::ConfigManager() 
{
	loadConfig();
}

ConfigManager::~ConfigManager() {}

void ConfigManager::loadConfig()
{
	std::ifstream config;

	config.open("config.ini");
	if (!config.is_open())
	{
		LogManager::Instance()->logError("Could not find config.ini.");
		return;
	}	

	parseConfig(config);

	config.close();
}

void ConfigManager::parseConfig(std::ifstream& config)
{
	std::string line;
	while (std::getline(config, line))
	{
		std::stringstream fileline(line);
		std::string key;
		std::string value;

		if (std::getline(fileline, key, '='))
		{
			std::getline(fileline, value);	

			//To add a configurable value, add type to header and register here
			if (key == "DebugLogPath") { debugLogPath = value; }
			if (key == "AssetsPath") { assetsPath = value; }
			if (key == "DebugLogLevel") { debugLogLevel = StringToNumber(value); }
		}
	}
}

const std::string& ConfigManager::getDebugLogPath() { return debugLogPath; }
const std::string& ConfigManager::getAssetsPath() { return assetsPath; }
const int& ConfigManager::getDebugLogLevel() { return debugLogLevel; }
