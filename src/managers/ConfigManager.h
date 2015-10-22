#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H 

#include <fstream>
#include <string>
#include <map>

#include "../templates/Singleton.h"

class ConfigManager: public Singleton<ConfigManager>
{
	public:
		ConfigManager();
		~ConfigManager();

		const std::string& getConfigValue(const std::string& key);

	private:
		void loadConfig();
		void parseConfig(std::ifstream& config);

		std::string debugLogPath;
		std::map<std::string, std::string> configValues;

		ConfigManager(const ConfigManager&);
		void operator=(const ConfigManager&);
};

#endif
