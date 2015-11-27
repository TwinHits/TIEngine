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

const sf::Texture& AssetsManager::getTexture(const std::string& name)
{
	GlobalId id = HashManager::Instance()->getHash(name);
	return getTexture(id);
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

const sf::SoundBuffer& AssetsManager::getAudio(const std::string& name)
{
	GlobalId id = HashManager::Instance()->getHash(name);
	return getAudio(id);
}

void AssetsManager::parseAssets()
{
	for (boost::filesystem::directory_entry& i : boost::filesystem::directory_iterator(texturesPath))
	{
		sf::Texture t;
		t.loadFromFile(i.path().string());
		t.setSmooth(true);
		GlobalId id = HashManager::Instance()->getHash(i.path().string());
		textures[id] = t;
		LogManager::Instance()->logInfo("Loaded texture '" + i.path().string() + "'.");
	}

	for (boost::filesystem::directory_entry& i : boost::filesystem::directory_iterator(audioPath))
	{
		sf::SoundBuffer s;
		s.loadFromFile(i.path().string());
		GlobalId id = HashManager::Instance()->getHash(i.path().string());
		audio[id] = s;
		LogManager::Instance()->logInfo("Loaded audio '" + i.path().string() + "'.");
	}
}
