#include <string>

#include "AssetsManager.h"
#include "ConfigManager.h"
#include "LogManager.h"

AssetsManager::AssetsManager()
{
	assetsPath = ConfigManager::Instance()->getConfigValue("assetsPath");
}

AssetsManager::~AssetsManager() {}

const std::string& AssetsManager::getTexture(const std::string& t)
{
	if (false)
	{
		LogManager::Instance()->logError("Cannot open texture " + t + ".");
	}
	return t;
}

const std::string& AssetsManager::getAudio(const std::string& a)
{
	if (false)
	{
		LogManager::Instance()->logError("Cannot open audio " + a  + ".");
	}
	return a;
}

