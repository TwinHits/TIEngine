#include "pch.h"

#include "Constants.h"

//Test that when using a config file we cannot find that the default values are returned correctly.
TEST(ConfigManager, GetDebugLogPathDefault) {
	std::string expected = "logs/";
	std::string actual = TIE::ConfigManager::Instance()->getDebugLogPath();
	
	ASSERT_EQ(expected, actual);
}

TEST(ConfigManager, GetAssetsPathDefault) {
	std::string expected = "assets/";
	std::string actual = TIE::ConfigManager::Instance()->getAssetsPath();

	ASSERT_EQ(expected, actual);
}

TEST(ConfigManager, GetDebugLogLevelDefault) {
	int expected = 3;
	int actual = TIE::ConfigManager::Instance()->getDebugLogLevel();

	ASSERT_EQ(expected, actual);
}

TEST(ConfigManager, GetDefaultDisplayLanguageDefault) {
	Language expected = en_US;
	Language actual = TIE::ConfigManager::Instance()->getDefaultDisplayLanguage();

	ASSERT_EQ(expected, actual);
}

//Test when given a specific configuration file, the file is loaded correctly.
TEST(ConfigManager, LoadCustomConfigFile) {
	bool success = TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);
	ASSERT_TRUE(success);
}

//Test parsing the configuration values from a config file
TEST(ConfigManager, ParseConfigFile) {
	bool success = TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	std::string expectedAssets = "../../tests/assets/";
	std::string actualAssets = TIE::ConfigManager::Instance()->getAssetsPath();
	ASSERT_EQ(expectedAssets, actualAssets);

	std::string expectedLogs = "../../tests/logs/";
	std::string actualLogs = TIE::ConfigManager::Instance()->getDebugLogPath();
	ASSERT_EQ(expectedLogs, actualLogs);

	int expectedDebugLogLevel = 1;
	int actualDebugLogLevel = TIE::ConfigManager::Instance()->getDebugLogLevel();
	ASSERT_EQ(expectedDebugLogLevel, actualDebugLogLevel);

	Language expectedDefaultDisplayLanguage = ja_JP;
	Language actualDefaultDisplayLanguage = TIE::ConfigManager::Instance()->getDefaultDisplayLanguage();
	ASSERT_EQ(expectedDefaultDisplayLanguage, actualDefaultDisplayLanguage);
}


TEST(ConfigManager, SetDefaultDisplayLanguage) {
	TIE::ConfigManager::Instance()->setDefaultDisplayLanguage(es_ES);

	Language expected = es_ES;
	Language actual = TIE::ConfigManager::Instance()->getDefaultDisplayLanguage();

	ASSERT_EQ(expected, actual);
}

TEST(ConfigManager, SetDebugLogLevel) {
	TIE::ConfigManager::Instance()->setDebugLogLevel(2);

	int expected = 2;
	int actual = TIE::ConfigManager::Instance()->getDebugLogLevel();

	ASSERT_EQ(expected, actual);

}