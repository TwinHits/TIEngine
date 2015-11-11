#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <string>
#include <map>

#include <SFML/Graphics.hpp>
#include <boost/filesystem.hpp>

#include "../templates/Singleton.h"

class AssetsManager: public Singleton<AssetsManager>
{
	public:
		const sf::Texture& getTexture(unsigned long id);
		unsigned long getAudio(unsigned long id);

		AssetsManager();	
		~AssetsManager();

	private:
		boost::filesystem::path texturesPath;
		boost::filesystem::path audioPath;

		void parseAssets();

		std::map<unsigned long, sf::Texture> textures;

		AssetsManager(const AssetsManager&);
		void operator=(const AssetsManager&);
};

#endif
