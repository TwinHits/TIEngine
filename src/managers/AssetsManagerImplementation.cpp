#include "AssetsManager.h"
#include "ConfigManager.h"
#include "LogManager.h"
#include "HashManager.h"

AssetsManager::AssetsManager()
{
	std::string assetsPath = ConfigManager::Instance()->getAssetsPath();
	texturesPath = boost::filesystem::path(assetsPath + "textures");
	audioPath = boost::filesystem::path(assetsPath + "audio");

	this->parseAssets();
}

AssetsManager::~AssetsManager() {}

const sf::Texture& AssetsManager::getTexture(GlobalId id)
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

const sf::SoundBuffer& AssetsManager::getAudio(GlobalId id)
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
		GlobalId id = HashManager::Instance()->getNewGlobalId();
		sf::Texture t;
		t.loadFromFile(i.path().string());
		t.setSmooth(true);
		textures[id] = t;
		LogManager::Instance()->logInfo("Loaded texture '" + i.path().string() + "'.");
	}

	for (boost::filesystem::directory_entry& i : boost::filesystem::directory_iterator(audioPath))
	{
		GlobalId id = HashManager::Instance()->getNewGlobalId();
		sf::SoundBuffer s;
		s.loadFromFile(i.path().string());
		audio[id] = s;
		LogManager::Instance()->logInfo("Loaded audio '" + i.path().string() + "'.");
	}
}
