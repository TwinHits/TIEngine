#include "AssetsManager.h"
#include "ConfigManager.h"
#include "LogManager.h"
#include "HashManager.h"

using namespace TIE;

AssetsManager::AssetsManager()
{
	std::string assetsPath = ConfigManager::Instance()->getAssetsPath();
	texturesPath = boost::filesystem::path(assetsPath + "textures");
	audioPath = boost::filesystem::path(assetsPath + "audio");
	fontsPath = boost::filesystem::path(assetsPath + "fonts");

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
		LogManager::Instance()->logError("Cannot open texture "  + std::to_string(id) + "'.");
		return textures[HashManager::Instance()->getHash("missing_texture.png")];
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

const sf::Font& AssetsManager::getFont(GlobalId id)
{
	if (fonts.find(id) != fonts.end())
	{
		return fonts[id];
	}
	else
	{
		LogManager::Instance()->logError("Cannot open audio '" + std::to_string(id) + "'.");
		return fonts[id];
	}
}

const sf::Font& AssetsManager::getFont(const std::string& name)
{
	GlobalId id = HashManager::Instance()->getHash(name);
	return getFont(id);
}

void AssetsManager::parseAssets()
{
	try
	{
		if (boost::filesystem::exists(texturesPath))
		{
			if (boost::filesystem::is_directory(texturesPath))
			{

				for (boost::filesystem::directory_entry& i : boost::filesystem::directory_iterator(texturesPath))
				{
					sf::Texture t;
					t.loadFromFile(i.path().string());
					GlobalId id = HashManager::Instance()->getHash(i.path().filename().string());
					textures[id] = t;
					LogManager::Instance()->logInfo("Loaded texture '" + i.path().string() + "'.");
				}
			}
		}
		else
		{
			LogManager::Instance()->logError("Textures folder does not exist.");
		}
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		LogManager::Instance()->logError("Textures folder error: " + std::string(e.what()));
	}

	try
	{
		if (boost::filesystem::exists(audioPath))
		{
			if (boost::filesystem::is_directory(audioPath))
			{
				for (boost::filesystem::directory_entry& i : boost::filesystem::directory_iterator(audioPath))
				{
					sf::SoundBuffer s;
					s.loadFromFile(i.path().string());
					GlobalId id = HashManager::Instance()->getHash(i.path().filename().string());
					audio[id] = s;
					LogManager::Instance()->logInfo("Loaded audio '" + i.path().string() + "'.");
				}
			}
		}
		else
		{
			LogManager::Instance()->logError("Audio folder does not exist.");
		}
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		LogManager::Instance()->logError("Audio folder error: " + std::string(e.what()));
	}

	try
	{
		if (boost::filesystem::exists(fontsPath))
		{
			if (boost::filesystem::is_directory(fontsPath))
			{
				for (boost::filesystem::directory_entry& i : boost::filesystem::directory_iterator(fontsPath))
				{
					sf::Font f;
					f.loadFromFile(i.path().string());
					GlobalId id = HashManager::Instance()->getHash(i.path().filename().string());
					fonts[id] = f;
					LogManager::Instance()->logInfo("Loaded font '" + i.path().string() + "'.");
				}
			}
		}
		else
		{
			LogManager::Instance()->logError("Fonts folder does not exist.");
		}
	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		LogManager::Instance()->logError("Fonts folder error: " + std::string(e.what()));
	}
}
