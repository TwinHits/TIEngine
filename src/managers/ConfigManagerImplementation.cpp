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
			if (key == "assetsPath") assetsPath = value;
			if (key == "loggingLevel") loggingLevel = StringToNumber(value);
		}
	}
}

const std::string& ConfigManager::getAssetsPath() { return assetsPath; }
const int& ConfigManager::getLoggingLevel() { return loggingLevel; }
