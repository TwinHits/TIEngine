#include "AssetsManager.h"
#include "ConfigManager.h"
#include "LogManager.h"
#include "HashManager.h"

AssetsManager::AssetsManager()
{
	std::string assetsPath = ConfigManager::Instance()->getAssetsPath();
	texturesPath = boost::filesystem::path(assetsPath + "textures");
	audioPath = boost::filesystem::path(assetsPath + "audio");

	parseAssets();
}

AssetsManager::~AssetsManager() {}

const sf::Texture& AssetsManager::getTexture(unsigned long id)
{
	if (textures.find(id) != textures.end())
	{
		return textures[id];
	}
	else
	{
		LogManager::Instance()->logError("Cannot open audio '" + std::to_string(id) + "'.");
		return textures[id];
	}
}

const std::string& AssetsManager::getAudio(unsigned long id)
{
	if (audio.find(id) != audio.end())
	{
		return audio[id];
	}
	else
	{
		LogManager::Instance()->logError("Cannot open audio '" + std::to_string(id) + "'.");
		return audio[id];
	}
}

void AssetsManager::parseAssets()
{
	for (boost::filesystem::directory_entry& i : boost::filesystem::directory_iterator(texturesPath))
	{
		unsigned long id = HashManager::Instance()->getNewHash();
		sf::Texture t;
		t.loadFromFile(i.path().string());
		textures[id] = t;
		LogManager::Instance()->logInfo("Loaded texture '" + i.path().string() + "'.");
	}

	for (boost::filesystem::directory_entry& i : boost::filesystem::directory_iterator(audioPath))
	{
		unsigned long id = HashManager::Instance()->getNewHash();
		std::string a = "a sound file";
		audio[id] = a;
		LogManager::Instance()->logInfo("Loaded audio '" + i.path().string() + "'.");
	}
}
