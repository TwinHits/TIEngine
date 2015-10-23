#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <string>

#include "../templates/Singleton.h"

class AssetsManager: public Singleton<AssetsManager>
{
	public:
		const std::string& getTexture(const std::string&);
		const std::string& getAudio(const std::string&);

		AssetsManager();	
		~AssetsManager();

	private:
		std::string assetsPath;

		AssetsManager(const AssetsManager&);
		void operator=(const AssetsManager&);
};

#endif
