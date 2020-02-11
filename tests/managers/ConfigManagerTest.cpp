#include "../pch.h"

#include "../Constants.h"

//Test that when using a config file we cannot find that the default values are returned correctly.
TEST(ConfigManager, GetDebugLogPathDefault) {
	TIE::ConfigManager::Instance()->restoreDefaultConfiguration();

	std::string expected = "logs/";
	std::string actual = TIE::ConfigManager::Instance()->getDebugLogPath();
	
	ASSERT_EQ(expected, actual);
}

TEST(ConfigManager, GetAssetsPathDefault) {
	TIE::ConfigManager::Instance()->restoreDefaultConfiguration();

	std::string expected = "assets/";
	std::string actual = TIE::ConfigManager::Instance()->getAssetsPath();

	ASSERT_EQ(expected, actual);
}

TEST(ConfigManager, GetDebugLogLevelDefault) {
	TIE::ConfigManager::Instance()->restoreDefaultConfiguration();
	
	TIE::LogLevel expected = TIE::LogLevel::INFO;
	TIE::LogLevel actual = TIE::ConfigManager::Instance()->getDebugLogLevel();

	ASSERT_EQ(expected, actual);
}

TEST(ConfigManager, GetDefaultDisplayLanguageDefault) {
	TIE::ConfigManager::Instance()->restoreDefaultConfiguration();

	TIE::Language expected = TIE::en_US;
	TIE::Language actual = TIE::ConfigManager::Instance()->getDefaultDisplayLanguage();

	ASSERT_EQ(expected, actual);
}

//Test when given a specific configuration file, the file is loaded correctly.
TEST(ConfigManager, LoadCustomConfigFile) {
	ASSERT_TRUE(TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE));
}

//Test parsing the configuration values from a config file
TEST(ConfigManager, ParseConfigFile) {
	ASSERT_TRUE(TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE));

	std::string expectedAssets = "../assets/";
	std::string actualAssets = TIE::ConfigManager::Instance()->getAssetsPath();
	ASSERT_EQ(expectedAssets, actualAssets);

	std::string expectedLogs = "logs/";
	std::string actualLogs = TIE::ConfigManager::Instance()->getDebugLogPath();
	ASSERT_EQ(expectedLogs, actualLogs);

	TIE::LogLevel expectedDebugLogLevel = TIE::LogLevel::DEBUG;
	TIE::LogLevel actualDebugLogLevel = TIE::ConfigManager::Instance()->getDebugLogLevel();
	ASSERT_EQ(expectedDebugLogLevel, actualDebugLogLevel);

	TIE::Language expectedDefaultDisplayLanguage = TIE::ja_JP;
	TIE::Language actualDefaultDisplayLanguage = TIE::ConfigManager::Instance()->getDefaultDisplayLanguage();
	ASSERT_EQ(expectedDefaultDisplayLanguage, actualDefaultDisplayLanguage);
}


TEST(ConfigManager, SetDefaultDisplayLanguage) {
	TIE::ConfigManager::Instance()->setDefaultDisplayLanguage(TIE::es_ES);

	TIE::Language expected = TIE::es_ES;
	TIE::Language actual = TIE::ConfigManager::Instance()->getDefaultDisplayLanguage();

	ASSERT_EQ(expected, actual);
}


TEST(ConfigManager, SetDebugLogLevel) {
	TIE::ConfigManager::Instance()->setDebugLogLevel(TIE::LogLevel::WARN);

	TIE::LogLevel expected = TIE::LogLevel::WARN;
	TIE::LogLevel actual = TIE::ConfigManager::Instance()->getDebugLogLevel();

	ASSERT_EQ(expected, actual);
}


TEST(ConfigManager, RestoreDefaultConfiguration) {
	ASSERT_TRUE(TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE));

	std::string expectedAssets = "../assets/";
	std::string actualAssets = TIE::ConfigManager::Instance()->getAssetsPath();
	ASSERT_EQ(expectedAssets, actualAssets);

	TIE::ConfigManager::Instance()->restoreDefaultConfiguration();

	std::string expected = "assets/";
	std::string actual = TIE::ConfigManager::Instance()->getAssetsPath();

	ASSERT_EQ(expected, actual);
}
