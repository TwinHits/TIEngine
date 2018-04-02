#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H 

#include <fstream>
#include <string>

#include "templates/Singleton.h"

#include "objects/Language.h"

namespace TIE {

class ConfigManager: public Singleton<ConfigManager> {
	//Singleton manager of engine side configurable values defined in
	//config.ini. Stores default values in case of no file found.
	public:
		ConfigManager();
		~ConfigManager();
		
		const std::string& getDebugLogPath();
		const std::string& getAssetsPath();
		const int& getDebugLogLevel();
		const Language& getDefaultDisplayLanguage();
		bool loadConfigFile(std::string path);
		
	private:
		bool loadConfig(std::string path);
		void parseConfig(std::ifstream& config);
		Language parseLanguage(const std::string& s);

		std::string defaultConfigPath = "config.ini";

		//Possible values and their defaults
		std::string debugLogPath = "logs/";
		std::string assetsPath = "assets/";
		int debugLogLevel = 3;
		Language defaultDisplayLanguage = en_US;

		ConfigManager(const ConfigManager&);
		void operator=(const ConfigManager&);
};

}
#endif
