#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <boost/filesystem.hpp>

#include "objects/GlobalId.h"

#include "templates/Singleton.h"

namespace TIE
{

	class AssetsManager: public Singleton<AssetsManager>
	{
		//Singleton manager for game assets. Parses every file found in the
		//config file defined assets folders.
		public:
			const sf::Texture& getTexture(GlobalId);
			const sf::Texture& getTexture(const std::string&);
			const sf::SoundBuffer& getAudio(GlobalId);
			const sf::SoundBuffer& getAudio(const std::string&);
			const sf::Font& getFont(GlobalId);
			const sf::Font& getFont(const std::string&);
	
			AssetsManager();	
			~AssetsManager();

		private:
			boost::filesystem::path texturesPath;
			boost::filesystem::path audioPath;
			boost::filesystem::path fontsPath;

			void parseAssets();

			std::map<GlobalId, sf::Texture> textures;
			std::map<GlobalId, sf::SoundBuffer> audio; 
			std::map<GlobalId, sf::Font> fonts;

			AssetsManager(const AssetsManager&);
			void operator=(const AssetsManager&);
	};

}

#endif
