#include <fstream>
#include <iostream>
#include <sstream>

#include "ConfigManager.h"

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
		std::cout << "Error: Could not open config file." << std::endl;
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

