#include "../pch.h"

#include "../Constants.h"
#include "../Helpers.h"

TEST(ConsoleManager, CreateConsole) {
	bool actual = TIE::ConsoleManager::Instance()->checkConsole();

	ASSERT_FALSE(actual);
}


TEST(ConsoleManager, ShowConsole) {
	bool expected = true;

	TIE::ConsoleManager::Instance()->showConsole();
	bool actual = TIE::ConsoleManager::Instance()->checkConsole();

	ASSERT_EQ(expected, actual);
}


TEST(ConsoleManager, HideConsole) {
	bool expected = false;

	TIE::ConsoleManager::Instance()->hideConsole();
	bool actual = TIE::ConsoleManager::Instance()->checkConsole();

	ASSERT_EQ(expected, actual);
}

TEST(ConsoleManager, RunCommand) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);
	TIE::ConsoleManager::Instance()->checkConsole();
	TIE::LogManager::Instance()->logDebug(TIE::TEST_NONSENSE_1);

	TIE::ConsoleManager::Instance()->runCommand(TIE::TEST_COMMAND);

	ASSERT_TRUE(TIE::CheckDebugLogForText(TIE::TEST_COMMAND_RUN_COMMAND));
}


TEST(ConsoleManager, SetDevConsole) {
	std::unique_ptr<TIE::DevConsole> devConsole = TIE::make_unique<TIE::DevConsole>();
	devConsole->setDraw(true);
	TIE::ConsoleManager::Instance()->hideConsole();
	
	TIE::ConsoleManager::Instance()->setDevConsole(std::move(devConsole));

	ASSERT_TRUE(TIE::ConsoleManager::Instance()->checkConsole());
}


//TEST(ConsoleManager, RenderDevConsole) {}
