#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <map>
#include <set>

#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "objects/GlobalId.h"

namespace TIE {

class AssetsManager: public Singleton<AssetsManager>, Manager {
	public:
		bool initialize();

		bool loadTexturesFromPath(const std::string&);
		bool loadFontsFromPath(const std::string&);
		bool loadAudioFromPath(const std::string&);

		sf::Texture& getTexture(GlobalId);
		sf::Texture& getTexture(const std::string&);
		const sf::SoundBuffer& getAudio(GlobalId);
		const sf::SoundBuffer& getAudio(const std::string&);
		const sf::Font& getFont(GlobalId);
		const sf::Font& getFont(const std::string&);

		AssetsManager() {};
		~AssetsManager() {};

	private:
		std::map<GlobalId, sf::Texture> textures;
		std::map<GlobalId, sf::SoundBuffer> audio; 
		std::map<GlobalId, sf::Font> fonts;

		std::set<boost::filesystem::path> texturesPathCache;
		std::set<boost::filesystem::path> audioPathCache;
		std::set<boost::filesystem::path> fontsPathCache;

		AssetsManager(const AssetsManager&);
		void operator=(const AssetsManager&) {};
};

}
#endif
