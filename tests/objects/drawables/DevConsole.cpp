#include "../../pch.h"

#include "../../Constants.h"
#include "../../Helpers.h"

TEST(DevConsole, RunKnownCommand) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);
	TIE::LogManager::Instance()->logCommand(TIE::TEST_NONSENSE_1);

	TIE::DevConsole devConsole = TIE::DevConsole();

	devConsole.processCommand(TIE::TEST_COMMAND);
	ASSERT_TRUE(TIE::CheckDebugLogForText(TIE::TEST_COMMAND_RUN_COMMAND));
}


TEST(DevConsole, RunUnknownCommand) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);
	TIE::LogManager::Instance()->logCommand(TIE::TEST_NONSENSE_2);

	TIE::DevConsole devConsole = TIE::DevConsole();

	devConsole.processCommand(TIE::TEST_NONSENSE_3);
	ASSERT_TRUE(TIE::CheckDebugLogForText(TIE::UNKNOWN_COMMAND_RUN_COMMAND));
}


TEST(DevConsole, Update) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);
	TIE::LogManager::Instance()->logInfo(TIE::TEST_NONSENSE_1);
	TIE::LogManager::Instance()->logWarn(TIE::TEST_NONSENSE_2);
	TIE::LogManager::Instance()->logError(TIE::TEST_NONSENSE_3);

	TIE::DevConsole devConsole = TIE::DevConsole();

	auto queueCopy = TIE::LogManager::Instance()->getQueueToDraw();
	auto& queue = TIE::LogManager::Instance()->getQueueToDraw();
	auto expected = queue.size();

	devConsole.update(1);

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
