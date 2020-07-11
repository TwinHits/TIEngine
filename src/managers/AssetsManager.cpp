#include "managers/AssetsManager.h"

#include "managers/ConfigManager.h"
#include "managers/LogManager.h"
#include "managers/HashManager.h"

using namespace TIE;

bool AssetsManager::initialize() {
	std::string assetsPath = ConfigManager::Instance()->getAssetsPath();

	this->loadTexturesFromPath(assetsPath + "textures");
	this->loadAudioFromPath(assetsPath + "audio");
	this->loadFontsFromPath(assetsPath + "fonts");

	return true;
}


sf::Texture& AssetsManager::getTexture(GlobalId id) {
	if (this->textures.find(id) != this->textures.end()) {
		return this->textures[id];
	} else {
		LogManager::Instance()->error("Cannot open texture "  + std::to_string(id) + "'.");
		return this->textures[HashManager::Instance()->getHash("missing_texture.png")];
	}
}


sf::Texture& AssetsManager::getTexture(const std::string& name) {
	GlobalId id = HashManager::Instance()->getHash(name);
	return this->getTexture(id);
}


const sf::SoundBuffer& AssetsManager::getAudio(GlobalId id) {
	if (this->audio.find(id) != this->audio.end()) {
		return this->audio[id];
	} else {
		LogManager::Instance()->error("Cannot open audio '" + std::to_string(id) + "'.");
		return this->audio[HashManager::Instance()->getHash("missing_audio.png")];
	}
}


const sf::SoundBuffer& AssetsManager::getAudio(const std::string& name) {
	GlobalId id = HashManager::Instance()->getHash(name);
	return this->getAudio(id);
}


const sf::Font& AssetsManager::getFont(GlobalId id) {
	if (this->fonts.find(id) != this->fonts.end()) {
		return this->fonts[id];
	} else {
		LogManager::Instance()->error("Cannot open font '" + std::to_string(id) + "'.");
		return this->fonts[HashManager::Instance()->getHash("missing_font.png")];
	}
}


const sf::Font& AssetsManager::getFont(const std::string& name) { 
	GlobalId id = HashManager::Instance()->getHash(name);
	return this->getFont(id);
}


bool AssetsManager::loadTexturesFromPath(const std::string& folder) {
	try {
		boost::filesystem::path path = boost::filesystem::path(folder);
		if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path)) {
			this->fontsPathCache.insert(path);
			for (boost::filesystem::directory_entry& i : boost::filesystem::directory_iterator(path)) {
				sf::Texture t;
				if (t.loadFromFile(i.path().string())) {
					GlobalId id = HashManager::Instance()->getHash(i.path().filename().string());
					this->textures[id] = t;
					LogManager::Instance()->info("Loading texture '" + i.path().string() + ". Id: " + std::to_string(id));
				} else {
					LogManager::Instance()->error("SFML Texture load error: Cannot load " + i.path().string());
				}
			}
			return true;
		} else {
			if (!boost::filesystem::exists(path)) {
				LogManager::Instance()->error("Path '" + path.string() + "' does not exist.");
			} else if (!boost::filesystem::is_directory(path)) {
				LogManager::Instance()->error("Path '" + path.string() + "' is not a directory.");
			}
			return false;
		}
	} catch (const boost::filesystem::filesystem_error& e) {
		LogManager::Instance()->error("Boost Textures load error: " + std::string(e.what()));
		return false;
	}
}


bool AssetsManager::loadAudioFromPath(const std::string& folder) {
	try {
		boost::filesystem::path path = boost::filesystem::path(folder);
		if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path)) {
			this->audioPathCache.insert(path);
			for (boost::filesystem::directory_entry& i : boost::filesystem::directory_iterator(path)) {
				sf::SoundBuffer s;
				if (s.loadFromFile(i.path().string())) {
					GlobalId id = HashManager::Instance()->getHash(i.path().filename().string());
					this->audio[id] = s;
					LogManager::Instance()->info("Loaded audio '" + i.path().string() + "'. Id: " + std::to_string(id));
				} else {
					LogManager::Instance()->error("SFML audio load error: Cannot load " + i.path().string());
				}
			}
			return true;
		} else {
			if (!boost::filesystem::exists(path)) {
				LogManager::Instance()->error("Path '" + path.string() + "' does not exist.");
			} else if (!boost::filesystem::is_directory(path)) {
				LogManager::Instance()->error("Path '" + path.string() + "' is not a directory.");
			}
			return false;
		}
	} catch (const boost::filesystem::filesystem_error& e) {
		LogManager::Instance()->error("Boost Audio load error: " + std::string(e.what()));
		return false;
	}
}


bool AssetsManager::loadFontsFromPath(const std::string& folder) {
	try {
		boost::filesystem::path path = boost::filesystem::path(folder);
		if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path)) {
			this->fontsPathCache.insert(path);
			for (boost::filesystem::directory_entry& i : boost::filesystem::directory_iterator(path)) {
				sf::Font f;
				if (f.loadFromFile(i.path().string())) {
					GlobalId id = HashManager::Instance()->getHash(i.path().filename().string());
					this->fonts[id] = f;
					LogManager::Instance()->info("Loaded font '" + i.path().string() + "'. Id: " + std::to_string(id));
				}
				else {
					LogManager::Instance()->error("SFML Font load error: Cannot load " + i.path().string());
				}
			}
			return true;
		} else {
			if (!boost::filesystem::exists(path)) {
				LogManager::Instance()->error("Path '" + path.string() + "' does not exist.");
			} else if (!boost::filesystem::is_directory(path)) {
				LogManager::Instance()->error("Path '" + path.string() + "' is not a directory.");
			}
			return false;
		}
	} catch (const boost::filesystem::filesystem_error& e) {
		LogManager::Instance()->error("Boost Fonts load error: " + std::string(e.what()));
		return false;
	}
}

