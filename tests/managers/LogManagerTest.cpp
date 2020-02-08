#include "../pch.h"

#include "../Constants.h"
#include "../Helpers.h"

//Test that LogManager correctly communicates changes to the ConfigManager
TEST(LogManager, SetDebugLogLevel) {

	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::INFO);

	TIE::LogLevel expected = TIE::LogLevel::INFO;
	TIE::LogLevel actual = TIE::ConfigManager::Instance()->getDebugLogLevel();
	ASSERT_EQ(expected, actual);
}


//Test that each log level value evaluates to the correct log level implementation
TEST(LogManager, LogLevelDebug) {
	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::DEBUG);
	ASSERT_TRUE(TIE::LogManager::Instance()->isDebugEnabled());
	ASSERT_TRUE(TIE::LogManager::Instance()->isInfoEnabled());
	ASSERT_TRUE(TIE::LogManager::Instance()->isWarnEnabled());
	ASSERT_TRUE(TIE::LogManager::Instance()->isErrorEnabled());
}


TEST(LogManager, LogLevelInfo) {
	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::INFO);
	ASSERT_FALSE(TIE::LogManager::Instance()->isDebugEnabled());
	ASSERT_TRUE(TIE::LogManager::Instance()->isInfoEnabled());
	ASSERT_TRUE(TIE::LogManager::Instance()->isWarnEnabled());
	ASSERT_TRUE(TIE::LogManager::Instance()->isErrorEnabled());
}


TEST(LogManager, LogLevelWarn) {
	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::WARN);
	ASSERT_FALSE(TIE::LogManager::Instance()->isDebugEnabled());
	ASSERT_FALSE(TIE::LogManager::Instance()->isInfoEnabled());
	ASSERT_TRUE(TIE::LogManager::Instance()->isWarnEnabled());
	ASSERT_TRUE(TIE::LogManager::Instance()->isErrorEnabled());
}


TEST(LogManager, LogLevelError) {
	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::ERROR);
	ASSERT_FALSE(TIE::LogManager::Instance()->isDebugEnabled());
	ASSERT_FALSE(TIE::LogManager::Instance()->isInfoEnabled());
	ASSERT_FALSE(TIE::LogManager::Instance()->isWarnEnabled());
	ASSERT_TRUE(TIE::LogManager::Instance()->isErrorEnabled());
}


//Check if text logged is correctly written to a file
TEST(LogManager, LogDebugToFile) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);

	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::DEBUG);
	TIE::LogManager::Instance()->logDebug(TIE::TEST_NONSENSE_1);
	bool checkSuccess = TIE::CheckDebugLogForText(TIE::DEBUG_LEVEL_PREFIX + TIE::TEST_NONSENSE_1);
	ASSERT_TRUE(checkSuccess);
}


TEST(LogManager, LogInfoToFile) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);

	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::INFO);
	TIE::LogManager::Instance()->logInfo(TIE::TEST_NONSENSE_2);
	bool checkSuccess = TIE::CheckDebugLogForText(TIE::INFO_LEVEL_PREFIX + TIE::TEST_NONSENSE_2);
	ASSERT_TRUE(checkSuccess);
}


TEST(LogManager, LogWarnToFile) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);

	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::INFO);
	TIE::LogManager::Instance()->logWarn(TIE::TEST_NONSENSE_3);
	bool checkSuccess = TIE::CheckDebugLogForText(TIE::WARN_LEVEL_PREFIX + TIE::TEST_NONSENSE_3);
	ASSERT_TRUE(checkSuccess);
}


TEST(LogManager, LogErrorToFile) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);

	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::INFO);
	TIE::LogManager::Instance()->logError(TIE::TEST_NONSENSE_4);
	bool checkSuccess = TIE::CheckDebugLogForText(TIE::ERROR_LEVEL_PREFIX + TIE::TEST_NONSENSE_4);
	ASSERT_TRUE(checkSuccess);
}


TEST(LogManager, LogCommandToFile) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);

	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::INFO);
	TIE::LogManager::Instance()->logCommand(TIE::TEST_NONSENSE_1);
	bool checkSuccess = TIE::CheckDebugLogForText(TIE::COMMAND_LEVEL_PREFIX + TIE::TEST_NONSENSE_1);
	ASSERT_TRUE(checkSuccess);
}


//Get all text logged this session and make sure it has everything.
TEST(LogManager, GetQueueToDraw) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);

	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::INFO);
	TIE::LogManager::Instance()->logInfo(TIE::TEST_NONSENSE_1);

	std::queue<std::string> queueToDraw = TIE::LogManager::Instance()->getQueueToDraw();
	ASSERT_TRUE(!queueToDraw.empty());
	ASSERT_TRUE(queueToDraw.back().find(TIE::INFO_LEVEL_PREFIX + TIE::TEST_NONSENSE_1, 0));
}