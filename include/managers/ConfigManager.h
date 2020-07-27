#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H 

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <fstream>
#include <map>
#include <string>

#include "objects/enumeration/LogLevel.h"	
#include "objects/enumeration/Language.h"

namespace TIE {

class ConfigManager: public Singleton<ConfigManager>, Manager {
	//Singleton manager of engine side configurable values defined in
	//config.ini. Stores default values in case of no file found.
	public:
		bool initialize();
		
		bool loadConfigFile(const std::string& path);

		const std::string& getDebugLogPath();
		const std::string& getAssetsPath();
		LogLevel getDebugLogLevel();
		const Language& getDefaultDisplayLanguage();
		const bool getShowMousePtrCoords();
		const bool getShowDegreeGuide();
		const std::string& getStartUpScript();

		void setDefaultDisplayLanguage(const Language& defaultDisplayLanguage);
		void setDebugLogLevel(LogLevel debugLogLevel);

		void restoreDefaultConfiguration();
		
		ConfigManager() {};
		~ConfigManager() {};
	private:
		bool loadConfig(const std::string& path);
		void parseConfig(std::ifstream& config);

		std::string defaultConfigPath = "config.ini";

		//Possible values and their defaults
		std::string defaultDebugLogPath = "logs/";
		std::string defaultAssetsPath = "assets/";
		LogLevel defaultDebugLogLevel = LogLevel::INFO;
		Language defaultDefaultDisplayLanguage = Language::en_US;
		bool defaultShowMousePtrCoords = false;
		bool defaultShowDegreeGuide = false;
		std::string defaultStartUpScript = "";

		std::string debugLogPath = defaultDebugLogPath;
		std::string assetsPath = defaultAssetsPath;
		LogLevel debugLogLevel = defaultDebugLogLevel;
		Language defaultDisplayLanguage = defaultDefaultDisplayLanguage;
		bool showMousePtrCoords = defaultShowMousePtrCoords;
		bool showDegreeGuide = defaultShowDegreeGuide;
		std::string startUpScript = defaultStartUpScript;

		ConfigManager(const ConfigManager&);
		void operator=(const ConfigManager&) {};
};

}
#endif
