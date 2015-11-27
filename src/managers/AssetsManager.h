#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <boost/filesystem.hpp>

#include "../objects/GlobalId.h"

#include "../templates/Singleton.h"

class AssetsManager: public Singleton<AssetsManager>
{
	public:
		const sf::Texture& getTexture(GlobalId);
		const sf::Texture& getTexture(const std::string&);
		const sf::SoundBuffer& getAudio(GlobalId);
		const sf::SoundBuffer& getAudio(const std::string&);

		AssetsManager();	
		~AssetsManager();

	private:
		boost::filesystem::path texturesPath;
		boost::filesystem::path audioPath;

		void parseAssets();

		std::map<GlobalId, sf::Texture> textures;
		std::map<GlobalId, sf::SoundBuffer> audio; 

		AssetsManager(const AssetsManager&);
		void operator=(const AssetsManager&);
};

#endif
