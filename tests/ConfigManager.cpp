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
	TIE::LogLevel expected = TIE::LogLevel::INFO;
	TIE::LogLevel actual = TIE::ConfigManager::Instance()->getDebugLogLevel();

	ASSERT_EQ(expected, actual);
}

TEST(ConfigManager, GetDefaultDisplayLanguageDefault) {
	TIE::Language expected = TIE::en_US;
	TIE::Language actual = TIE::ConfigManager::Instance()->getDefaultDisplayLanguage();

	ASSERT_EQ(expected, actual);
}

TEST(ConfigManager, GetDatabaseConnectionStringDefault) {
	const std::string expected = "dbname=tiengine user=tie_admin password=123456 hostaddr=127.0.0.1 port=5432";
	const std::string actual = TIE::ConfigManager::Instance()->getDatabaseConnectionString();

	ASSERT_EQ(expected, actual);
}

//Test when given a specific configuration file, the file is loaded correctly.
TEST(ConfigManager, LoadCustomConfigFile) {
	ASSERT_TRUE(TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE));
}

//Test parsing the configuration values from a config file
TEST(ConfigManager, ParseConfigFile) {
	ASSERT_TRUE(TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE));

	std::string expectedAssets = "../../tests/assets/";
	std::string actualAssets = TIE::ConfigManager::Instance()->getAssetsPath();
	ASSERT_EQ(expectedAssets, actualAssets);

	std::string expectedLogs = "../../tests/logs/";
	std::string actualLogs = TIE::ConfigManager::Instance()->getDebugLogPath();
	ASSERT_EQ(expectedLogs, actualLogs);

	TIE::LogLevel expectedDebugLogLevel = TIE::LogLevel::ERROR;
	TIE::LogLevel actualDebugLogLevel = TIE::ConfigManager::Instance()->getDebugLogLevel();
	ASSERT_EQ(expectedDebugLogLevel, actualDebugLogLevel);

	TIE::Language expectedDefaultDisplayLanguage = TIE::ja_JP;
	TIE::Language actualDefaultDisplayLanguage = TIE::ConfigManager::Instance()->getDefaultDisplayLanguage();
	ASSERT_EQ(expectedDefaultDisplayLanguage, actualDefaultDisplayLanguage);

	std::string expectedDBString = "dbname=testtiedb user=root password=654321 hostaddr=localhost port=2345";
	std::string actualDBString = TIE::ConfigManager::Instance()->getDatabaseConnectionString();
	ASSERT_EQ(expectedDBString, actualDBString);

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
