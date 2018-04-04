#include "pch.h"

//Test that LogManager correctly communicates changes to the ConfigManager
TEST(LogManager, SetDebugLogLevel) {
	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::INFO);

	TIE::LogLevel expected = TIE::LogLevel::INFO;
	TIE::LogLevel actual = TIE::ConfigManager::Instance()->getDebugLogLevel();
	ASSERT_EQ(expected, actual);
}

//Test that each log level value evaluates to the correct log level implementation
TEST(LogManager, LogLevelInfoLevels) {
	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::INFO);
	ASSERT_TRUE(TIE::LogManager::Instance()->isInfoEnabled());
	ASSERT_TRUE(TIE::LogManager::Instance()->isWarnEnabled());
	ASSERT_TRUE(TIE::LogManager::Instance()->isErrorEnabled());
}


TEST(LogManager, LogLevelWarnLevels) {
	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::WARN);
	ASSERT_FALSE(TIE::LogManager::Instance()->isInfoEnabled());
	ASSERT_TRUE(TIE::LogManager::Instance()->isWarnEnabled());
	ASSERT_TRUE(TIE::LogManager::Instance()->isErrorEnabled());
}


TEST(LogManager, LogLevelErrorLevels) {
	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::ERROR);
	ASSERT_FALSE(TIE::LogManager::Instance()->isInfoEnabled());
	ASSERT_FALSE(TIE::LogManager::Instance()->isWarnEnabled());
	ASSERT_TRUE(TIE::LogManager::Instance()->isErrorEnabled());
}

TEST(LogManager, LogInfoToFile) {}
TEST(LogManager, LogWarnToFile) {}
TEST(LogManager, LogErrorToFile) {}
TEST(LogManager, LogCommandToFile) {}
TEST(LogManager, GetQueueToDraw) {}