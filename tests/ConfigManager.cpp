#include "pch.h"

//Calling for a configuration value without providing a configuration file and when 
//we can't find the default configuration file should return a default value
TEST(ConfigManager, GetDebugLogPath_DefaultPath) {
	//reset to default path
	TIE::ConfigManager::Instance()->loadConfigFile("config.ini");

	std::string expected = "/logs";
	std::string actual = TIE::ConfigManager::Instance()->getDebugLogPath();
	
	ASSERT_EQ(expected, actual);
}

TEST(ConfigManager, GetAssetsPath_DefaultPath) {
	//reset to default path
	TIE::ConfigManager::Instance()->loadConfigFile("config.ini");

	std::string expected = "/assets";
	std::string actual = TIE::ConfigManager::Instance()->getAssetsPath();

	ASSERT_EQ(expected, actual);
}

TEST(ConfigManager, GetDebugLogLevel_DefaultPath) {
	//reset to default path
	TIE::ConfigManager::Instance()->loadConfigFile("config.ini");

	int expected = 3;
	int actual = TIE::ConfigManager::Instance()->getDebugLogLevel();

	ASSERT_EQ(expected, actual);
}

TEST(ConfigManager, GetDefaultDisplayLanguage_DefaultPath) {
	//reset to default path
	TIE::ConfigManager::Instance()->loadConfigFile("config.ini");

	Language expected = en_US;
	Language actual = TIE::ConfigManager::Instance()->getDefaultDisplayLanguage();

	ASSERT_EQ(expected, actual);
}