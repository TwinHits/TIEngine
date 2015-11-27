#include <map>

#include <boost/filesystem.hpp>

#include "ConfigManager.h"
#include "LogManager.h"

#include "../utilities/StringToInt.h"

using namespace TIE;

ConfigManager::ConfigManager() 
{
	loadConfig();
}

ConfigManager::~ConfigManager() {}

void ConfigManager::loadConfig()
{
	auto configPath = boost::filesystem::path("config.ini");
	if (exists(configPath))
	{ std::ifstream config;

		config.open("config.ini");
		if (!config.is_open())
		{
			return;
		}	

		parseConfig(config);

		config.close();
	}
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

			if (key == "DebugLogPath") { debugLogPath = value; }
			if (key == "AssetsPath") { assetsPath = value; }
			if (key == "DebugLogLevel") { debugLogLevel = StringToInt(value); }
			if (key == "defaultDisplayLanguage") { defaultDisplayLanguage = parseLanguage(value); }
		}
	}
}

Language ConfigManager::parseLanguage(const std::string& s)
{
	//defaultDisplayLanguage is stored as a string in the config.ini, and must
	//be converted to it's enumerated type.
	std::map<std::string, Language> languages;
	languages["EN"] = EN;
	languages["ES"] = ES;
	languages["FR"] = FR;
	languages["DE"] = DE;
	languages["JP"] = JP;
	languages["RU"] = RU;
	languages["AR"] = AR;
	languages["CN"] = CN;

	Language l = languages[s];
	if (l == 0)
		return EN;
	else
		return l;
}

const std::string& ConfigManager::getDebugLogPath() { return debugLogPath; }
const std::string& ConfigManager::getAssetsPath() { return assetsPath; }
const int& ConfigManager::getDebugLogLevel() { return debugLogLevel; }
const Language& ConfigManager::getDefaultDisplayLanguage() { return defaultDisplayLanguage; }
