#include "../pch.h"

#include "../Constants.h"
#include "../Helpers.h"

TEST(WindowManager, AddWindowDefaultSettings) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);

	const sf::RenderWindow& window = TIE::WindowManager::Instance()->addWindow();

	sf::Vector2u actualSize = window.getSize();
	sf::Vector2u expectedSize(800, 600);
	ASSERT_EQ(expectedSize.x, actualSize.x);
	ASSERT_EQ(expectedSize.y, actualSize.y);

	const sf::ContextSettings& actualSettings = window.getSettings();
	const sf::ContextSettings expectedSettings  = sf::ContextSettings();
	ASSERT_EQ(expectedSettings.antialiasingLevel, actualSettings.antialiasingLevel);
	ASSERT_EQ(expectedSettings.attributeFlags, actualSettings.attributeFlags);
	ASSERT_EQ(expectedSettings.Core, actualSettings.Core);
	ASSERT_EQ(expectedSettings.Debug, actualSettings.Debug);
	ASSERT_EQ(expectedSettings.depthBits, actualSettings.depthBits);
	ASSERT_EQ(expectedSettings.stencilBits, actualSettings.stencilBits);

	TIE::WindowManager::Instance()->removeWindow();
}


TEST(WindowManager, RemoveWindow) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);

	const sf::RenderWindow& window = TIE::WindowManager::Instance()->addWindow();
	TIE::WindowManager::Instance()->removeWindow();
	TIE::LogManager::Instance()->logWarn(TIE::TEST_NONSENSE_4);
	const sf::RenderWindow& window2 = TIE::WindowManager::Instance()->addWindow();
	ASSERT_FALSE(TIE::CheckDebugLogForText(TIE::WARN_LEVEL_PREFIX + TIE::SECOND_WINDOW_WARNING));

	TIE::WindowManager::Instance()->removeWindow();
}


TEST(WindowManager, GetWindowNoInitializedWindow) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);

	TIE::WindowManager::Instance()->removeWindow();
	const sf::RenderWindow& window = TIE::WindowManager::Instance()->getWindow();

	sf::Vector2u actualSize = window.getSize();
	sf::Vector2u expectedSize(800, 600);
	ASSERT_EQ(expectedSize.x, actualSize.x);
	ASSERT_EQ(expectedSize.y, actualSize.y);

	const sf::ContextSettings& actualSettings = window.getSettings();
	const sf::ContextSettings expectedSettings = sf::ContextSettings();
	ASSERT_EQ(expectedSettings.antialiasingLevel, actualSettings.antialiasingLevel);
	ASSERT_EQ(expectedSettings.attributeFlags, actualSettings.attributeFlags);
	ASSERT_EQ(expectedSettings.Core, actualSettings.Core);
	ASSERT_EQ(expectedSettings.Debug, actualSettings.Debug);
	ASSERT_EQ(expectedSettings.depthBits, actualSettings.depthBits);
	ASSERT_EQ(expectedSettings.stencilBits, actualSettings.stencilBits);

	TIE::WindowManager::Instance()->removeWindow();
}


TEST(WindowManager, GetWindowAlreadyExists) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);

	TIE::WindowManager::Instance()->addWindow();
	TIE::LogManager::Instance()->logWarn(TIE::TEST_NONSENSE_3);
	const sf::RenderWindow& window = TIE::WindowManager::Instance()->getWindow();
	ASSERT_FALSE(TIE::CheckDebugLogForText(TIE::WARN_LEVEL_PREFIX + TIE::NO_WINDOW_TO_GET_WARNING));

	TIE::WindowManager::Instance()->removeWindow();
}


TEST(WindowManager, AddSecondWindow) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);

	const sf::RenderWindow& window1 = TIE::WindowManager::Instance()->addWindow();
	const sf::RenderWindow& window2 = TIE::WindowManager::Instance()->addWindow();

	TIE::WindowManager::Instance()->removeWindow();
}


TEST(WindowManager, GetWindowSize) {
	const sf::RenderWindow& window = TIE::WindowManager::Instance()->addWindow();
	sf::Vector2u expected = window.getSize();
	sf::Vector2i actual = TIE::WindowManager::Instance()->getWindowSize();
	ASSERT_EQ(expected.x, actual.x);
	ASSERT_EQ(expected.y, actual.y);

	TIE::WindowManager::Instance()->removeWindow();
}


TEST(WindowManager, GetTitle) {
	std::string expected = TIE::TEST_NONSENSE_1;
	TIE::WindowManager::Instance()->addWindow(sf::VideoMode(800, 600), expected);
	const std::string& actual = TIE::WindowManager::Instance()->getTitle();
	ASSERT_EQ(expected, actual);

	TIE::WindowManager::Instance()->removeWindow();
}
