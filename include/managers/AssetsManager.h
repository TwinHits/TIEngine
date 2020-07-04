#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include "templates/Singleton.h"

#include <map>

#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "objects/GlobalId.h"

namespace TIE {

class AssetsManager: public Singleton<AssetsManager> {
	public:
		sf::Texture& getTexture(GlobalId);
		sf::Texture& getTexture(const std::string&);
		const sf::SoundBuffer& getAudio(GlobalId);
		const sf::SoundBuffer& getAudio(const std::string&);
		const sf::Font& getFont(GlobalId);
		const sf::Font& getFont(const std::string&);

		AssetsManager();	
		~AssetsManager() {};

	private:
		boost::filesystem::path texturesPath;
		boost::filesystem::path audioPath;
		boost::filesystem::path fontsPath;

		void parseAssets();

		std::map<GlobalId, sf::Texture> textures;
		std::map<GlobalId, sf::SoundBuffer> audio; 
		std::map<GlobalId, sf::Font> fonts;

		AssetsManager(const AssetsManager&);
		void operator=(const AssetsManager&) {};
};

}
#endif
