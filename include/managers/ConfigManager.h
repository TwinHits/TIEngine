#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H 

#include <fstream>
#include <map>
#include <string>

#include "templates/Singleton.h"

#include "objects/enumeration/LogLevel.h"	
#include "objects/enumeration/Language.h"

namespace TIE {

class ConfigManager: public Singleton<ConfigManager> {
	//Singleton manager of engine side configurable values defined in
	//config.ini. Stores default values in case of no file found.
	public:
		ConfigManager();
		~ConfigManager() {};
		
		bool loadConfigFile(const std::string& path);

		const std::string& getDebugLogPath();
		const std::string& getAssetsPath();
		const std::string& getScriptsPath();
		LogLevel getDebugLogLevel();
		const Language& getDefaultDisplayLanguage();
		const bool getShowMousePtrCoords();
		const bool getShowDegreeGuide();

		void setDefaultDisplayLanguage(const Language& defaultDisplayLanguage);
		void setDebugLogLevel(LogLevel debugLogLevel);

		void restoreDefaultConfiguration();
		
	private:
		bool loadConfig(const std::string& path);
		void parseConfig(std::ifstream& config);

		std::string defaultConfigPath = "config.ini";

		//Possible values and their defaults
		std::string defaultDebugLogPath = "../logs/";
		std::string defaultAssetsPath = "../assets/";
		std::string defaultScriptsPath = "../scripts/";
		LogLevel defaultDebugLogLevel = LogLevel::INFO;
		Language defaultDefaultDisplayLanguage = Language::en_US;
		bool defaultShowMousePtrCoords = false;
		bool defaultShowDegreeGuide = false;

		std::string debugLogPath = defaultDebugLogPath;
		std::string assetsPath = defaultAssetsPath;
		std::string scriptsPath = defaultScriptsPath;
		LogLevel debugLogLevel = defaultDebugLogLevel;
		Language defaultDisplayLanguage = defaultDefaultDisplayLanguage;
		bool showMousePtrCoords = defaultShowMousePtrCoords;
		bool showDegreeGuide = defaultShowDegreeGuide;

		ConfigManager(const ConfigManager&);
		void operator=(const ConfigManager&);
};

}
#endif
