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
		~ConfigManager();
		
		bool loadConfigFile(const std::string& path);

		const std::string& getDebugLogPath();
		const std::string& getAssetsPath();
		LogLevel getDebugLogLevel();
		const Language& getDefaultDisplayLanguage();
		const std::string& getDatabaseConnectionString();
		const bool getShowMousePtrCoords();

		void setDefaultDisplayLanguage(const Language& defaultDisplayLanguage);
		void setDebugLogLevel(LogLevel debugLogLevel);

		void restoreDefaultConfiguration();
		
	private:
		bool loadConfig(const std::string& path);
		void parseConfig(std::ifstream& config);
		const std::string assembleDatabaseConnectionString(std::map<std::string, std::string>);

		std::string defaultConfigPath = "config.ini";

		//Possible values and their defaults
		std::string debugLogPath = "logs/";
		std::string assetsPath = "assets/";
		LogLevel debugLogLevel = LogLevel::INFO;
		Language defaultDisplayLanguage = Language::en_US;
		std::string databaseConnectionString = "noconnectionstring";
		bool showMousePtrCoords = false;

		ConfigManager(const ConfigManager&);
		void operator=(const ConfigManager&);
};

}
#endif
