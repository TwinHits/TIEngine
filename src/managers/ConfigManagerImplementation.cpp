#include <fstream>
#include <sstream>

#include "ConfigManager.h"
#include "LogManager.h"

ConfigManager::ConfigManager() 
{
	loadConfig();
}

ConfigManager::~ConfigManager() {}

const std::string& ConfigManager::getConfigValue(const std::string& key)
{
	return configValues[key];
}

void ConfigManager::loadConfig()
{
	std::ifstream config;

	config.open("config.ini");
	if (!config)
	{
		LogManager::logCrashFile("Could not find config.ini.");
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
			configValues[key] = value;
		}
	}
}

