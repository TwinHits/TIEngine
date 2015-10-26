#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H 

#include <fstream>
#include <string>

#include "../templates/Singleton.h"

class ConfigManager: public Singleton<ConfigManager>
{
	public:
		ConfigManager();
		~ConfigManager();
		
		const std::string& getDebugLogPath();
		const std::string& getAssetsPath();
		const int& getDebugLogLevel();
			
	private:
		void loadConfig();
		void parseConfig(std::ifstream& config);

		//Configurable Values
		std::string debugLogPath = "";
		std::string assetsPath = "";
		int debugLogLevel = 3;

		ConfigManager(const ConfigManager&);
		void operator=(const ConfigManager&);
};

#endif
