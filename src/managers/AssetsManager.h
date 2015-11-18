#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <string>
#include <map>

#include <SFML/Graphics.hpp>
#include <boost/filesystem.hpp>

#include "../objects/GlobalId.h"

#include "../templates/Singleton.h"

class AssetsManager: public Singleton<AssetsManager>
{
	public:
		const sf::Texture& getTexture(GlobalId id);
		const std::string& getAudio(GlobalId id);

		AssetsManager();	
		~AssetsManager();

	private:
		boost::filesystem::path texturesPath;
		boost::filesystem::path audioPath;

		void parseAssets();

		std::map<GlobalId, sf::Texture> textures;
		std::map<GlobalId, std::string> audio; 

		AssetsManager(const AssetsManager&);
		void operator=(const AssetsManager&);
};

#endif
