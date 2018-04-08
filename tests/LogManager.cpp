#include "pch.h"

#include "Constants.h"

bool CheckDebugLogForText(const std::string& text);

//Test that LogManager correctly communicates changes to the ConfigManager
TEST(LogManager, SetDebugLogLevel) {
	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::INFO);

	TIE::LogLevel expected = TIE::LogLevel::INFO;
	TIE::LogLevel actual = TIE::ConfigManager::Instance()->getDebugLogLevel();
	ASSERT_EQ(expected, actual);
}

//Test that each log level value evaluates to the correct log level implementation
TEST(LogManager, LogLevelInfo) {
	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::INFO);
	ASSERT_TRUE(TIE::LogManager::Instance()->isInfoEnabled());
	ASSERT_TRUE(TIE::LogManager::Instance()->isWarnEnabled());
	ASSERT_TRUE(TIE::LogManager::Instance()->isErrorEnabled());
}


TEST(LogManager, LogLevelWarn) {
	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::WARN);
	ASSERT_FALSE(TIE::LogManager::Instance()->isInfoEnabled());
	ASSERT_TRUE(TIE::LogManager::Instance()->isWarnEnabled());
	ASSERT_TRUE(TIE::LogManager::Instance()->isErrorEnabled());
}


TEST(LogManager, LogLevelError) {
	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::ERROR);
	ASSERT_FALSE(TIE::LogManager::Instance()->isInfoEnabled());
	ASSERT_FALSE(TIE::LogManager::Instance()->isWarnEnabled());
	ASSERT_TRUE(TIE::LogManager::Instance()->isErrorEnabled());
}


//Check if text logged is correctly written to a file
TEST(LogManager, LogInfoToFile) {
	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::INFO);
	TIE::LogManager::Instance()->logInfo(TEST_NONSENSE_2);
	bool checkSuccess = CheckDebugLogForText(INFO_LEVEL_PREFIX + TEST_NONSENSE_2);
	ASSERT_TRUE(checkSuccess);
}


TEST(LogManager, LogWarnToFile) {
	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::INFO);
	TIE::LogManager::Instance()->logWarn(TEST_NONSENSE_3);
	bool checkSuccess = CheckDebugLogForText(WARN_LEVEL_PREFIX + TEST_NONSENSE_3);
	ASSERT_TRUE(checkSuccess);
}


TEST(LogManager, LogErrorToFile) {
	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::INFO);
	TIE::LogManager::Instance()->logError(TEST_NONSENSE_4);
	bool checkSuccess = CheckDebugLogForText(ERROR_LEVEL_PREFIX + TEST_NONSENSE_4);
	ASSERT_TRUE(checkSuccess);
}


TEST(LogManager, LogCommandToFile) {
	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::INFO);
	TIE::LogManager::Instance()->logCommand(TEST_NONSENSE_1);
	bool checkSuccess = CheckDebugLogForText(COMMAND_LEVEL_PREFIX + TEST_NONSENSE_1);
	ASSERT_TRUE(checkSuccess);
}


//Get all text logged this session and make sure it has everything.
TEST(LogManager, GetQueueToDraw) {
	TIE::LogManager::Instance()->setDebugLogLevel(TIE::LogLevel::INFO);
	TIE::LogManager::Instance()->logInfo(TEST_NONSENSE_1);

	std::queue<std::string> queueToDraw = TIE::LogManager::Instance()->getQueueToDraw();
	ASSERT_TRUE(!queueToDraw.empty());
	ASSERT_TRUE(queueToDraw.back().find(INFO_LEVEL_PREFIX + TEST_NONSENSE_1, 0));
}

//Helper method for making sure that the last line of the debuglog contains the provided text
bool CheckDebugLogForText(const std::string& text) {
	std::ifstream log;
	log.open(TIE::ConfigManager::Instance()->getDebugLogPath() + "debug.log", std::ios_base::app);
	if (!log.is_open()) {
		throw std::runtime_error("Failed to open debug log file: " + TIE::ConfigManager::Instance()->getDebugLogPath() + "debug.log");
	} else {
		std::string line = "";
		std::vector<std::string> lines;
		while (std::getline(log, line)) {
			lines.push_back(line);
		}

		const std::string& lastLine = lines.back();
		if (lastLine.find(text, 0) != std::string::npos) {
			log.close();
			return true;
		} else {
			log.close();
			return false;
		}
	}
	return false;
}