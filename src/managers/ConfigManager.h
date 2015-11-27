#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H 

#include <fstream>
#include <string>

#include "../templates/Singleton.h"

#include "../objects/Language.h"

namespace TIE
{

	class ConfigManager: public Singleton<ConfigManager>
	{
		public:
			ConfigManager();
			~ConfigManager();
		
			const std::string& getDebugLogPath();
			const std::string& getAssetsPath();
			const int& getDebugLogLevel();
			const Language& getDefaultDisplayLanguage();
			
		private:
			void loadConfig();
			void parseConfig(std::ifstream& config);
			Language parseLanguage(const std::string& s);

			//Configurable Values
			std::string debugLogPath = "";
			std::string assetsPath = "";
			int debugLogLevel = 3;
			Language defaultDisplayLanguage = EN;

			ConfigManager(const ConfigManager&);
			void operator=(const ConfigManager&);
	};

}
#endif
