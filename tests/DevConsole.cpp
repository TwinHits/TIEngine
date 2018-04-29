#include "pch.h"

#include "Constants.h"
#include "Helpers.h"

TEST(DevConsole, RunKnownCommand) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);
	TIE::LogManager::Instance()->logCommand(TEST_NONSENSE_1);

	TIE::DevConsole devConsole = TIE::DevConsole();

	devConsole.processCommand(TEST_COMMAND);
	ASSERT_TRUE(CheckDebugLogForText(TEST_COMMAND_RUN_COMMAND));
}


TEST(DevConsole, RunUnknownCommand) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);
	TIE::LogManager::Instance()->logCommand(TEST_NONSENSE_2);

	TIE::DevConsole devConsole = TIE::DevConsole();

	devConsole.processCommand(TEST_NONSENSE_3);
	ASSERT_TRUE(CheckDebugLogForText(UNKNOWN_COMMAND_RUN_COMMAND));
}


TEST(DevConsole, Update) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);
	TIE::LogManager::Instance()->logInfo(TEST_NONSENSE_1);
	TIE::LogManager::Instance()->logWarn(TEST_NONSENSE_2);
	TIE::LogManager::Instance()->logError(TEST_NONSENSE_3);

	TIE::DevConsole devConsole = TIE::DevConsole();

	auto queueCopy = TIE::LogManager::Instance()->getQueueToDraw();
	auto& queue = TIE::LogManager::Instance()->getQueueToDraw();
	auto expected = queue.size();

	devConsole.update();

	ASSERT_TRUE(queue.empty());

	auto& commandHistory = devConsole.getCommandHistory();
	auto actual = commandHistory.size();

	ASSERT_EQ(expected, actual);

	for (auto& c : commandHistory) {
		std::string expected = queueCopy.front();
		std::string actual = c.getText().getString();
		ASSERT_EQ(expected,actual);
		queueCopy.pop();
	}

}