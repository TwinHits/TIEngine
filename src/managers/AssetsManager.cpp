#include "managers/AssetsManager.h"

#include "managers/ConfigManager.h"
#include "managers/LogManager.h"
#include "managers/HashManager.h"
#include "objects/GlobalId.h"
#include "objects/assets/FontAsset.h"
#include "templates/MakeUnique.h"

using namespace TIE;

void AssetsManager::initialize() {
	std::string assetsPath = ConfigManager::Instance()->getAssetsPath();

	this->loadTexturesFromPath(assetsPath + "textures");
	this->loadAudioFromPath(assetsPath + "audio");
	this->loadFontsFromPath(assetsPath + "fonts");

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


const FontAsset& AssetsManager::getFont(GlobalId id) {
	if (this->fonts.find(id) != this->fonts.end()) {
		return *this->fonts[id];
	} else {
		LogManager::Instance()->error("Cannot open font " + std::to_string(id));
		return *this->fonts[HashManager::Instance()->getHash(ConfigManager::Instance()->getEngineFontName())];
	}
}


const FontAsset& AssetsManager::getFont(const std::string& name) { 
	GlobalId id = HashManager::Instance()->getHash(name);
	return this->getFont(id);
}


bool AssetsManager::loadTexturesFromPath(const std::string& folder) {
	return this->loadTexturesFromPath(boost::filesystem::path(folder));
}


bool AssetsManager::loadTexturesFromPath(const boost::filesystem::path& path) {
	try {
		if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path)) {
			for (boost::filesystem::directory_entry& file : boost::filesystem::directory_iterator(path)) {
				if (!boost::filesystem::is_directory(file)) {
					sf::Texture texture;
					if (texture.loadFromFile(file.path().string())) {
						GlobalId id = HashManager::Instance()->getHash(file.path().filename().string());
						this->textures[id] = texture;
						texture.setSmooth(true);
						LogManager::Instance()->info("Loaded texture '" + file.path().string() + ". Id: " + std::to_string(id));
					} else {
						LogManager::Instance()->error("SFML Texture load error: Cannot load " + file.path().string());
					}
				} else {
					this->loadTexturesFromPath(file.path());
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
	return this->loadAudioFromPath(boost::filesystem::path(folder));
}


bool AssetsManager::loadAudioFromPath(const boost::filesystem::path& path) {
	try {
		if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path)) {
			for (boost::filesystem::directory_entry& file : boost::filesystem::directory_iterator(path)) {
				if (!boost::filesystem::is_directory(file)) {
					sf::SoundBuffer soundBuffer;
                    if (soundBuffer.loadFromFile(file.path().string())) {
                        GlobalId id = HashManager::Instance()->getHash(file.path().filename().string());
                        this->audio[id] = soundBuffer;
                        LogManager::Instance()->info("Loaded audio '" + file.path().string() + "'. Id: " + std::to_string(id));
                    } else {
                        LogManager::Instance()->error("SFML audio load error: Cannot load " + file.path().string());
					}
				} else {
					this->loadAudioFromPath(file.path());
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
	return this->loadFontsFromPath(boost::filesystem::path(folder));
}


bool AssetsManager::loadFontsFromPath(const boost::filesystem::path& path) {
	try {
		if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path)) {
			for (boost::filesystem::directory_entry& file : boost::filesystem::directory_iterator(path)) {
				if (!boost::filesystem::is_directory(file)) {
					const std::string filename = file.path().filename().string();
					GlobalId id = HashManager::Instance()->getHash(filename);
					this->fonts[id] = TIE::make_unique<FontAsset>(filename, id);
                    if (this->fonts[id]->loadFromFile(file.path().string())) {
                        LogManager::Instance()->info("Loaded font '" + file.path().string() + "'. Id: " + std::to_string(id));
                    } else {
						LogManager::Instance()->error("SFML Font load error: Cannot load " + file.path().string());
					}
				} else {
					this->loadAudioFromPath(file.path());
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

