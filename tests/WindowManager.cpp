#include "pch.h"

#include "Constants.h"
#include "Helpers.h"

TEST(WindowManager, AddWindowDefaultSettings) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

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
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	const sf::RenderWindow& window = TIE::WindowManager::Instance()->addWindow();
	TIE::WindowManager::Instance()->removeWindow();
	TIE::LogManager::Instance()->logWarn(TEST_NONSENSE_4);
	const sf::RenderWindow& window2 = TIE::WindowManager::Instance()->addWindow();
	ASSERT_FALSE(CheckDebugLogForText(WARN_LEVEL_PREFIX + SECOND_WINDOW_WARNING));

	TIE::WindowManager::Instance()->removeWindow();
}


TEST(WindowManager, GetWindowNoWindow) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

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
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	TIE::WindowManager::Instance()->addWindow();
	TIE::LogManager::Instance()->logWarn(TEST_NONSENSE_3);
	const sf::RenderWindow& window = TIE::WindowManager::Instance()->getWindow();
	ASSERT_FALSE(CheckDebugLogForText(WARN_LEVEL_PREFIX + NO_WINDOW_TO_GET_WARNING));

	TIE::WindowManager::Instance()->removeWindow();
}


TEST(WindowManager, AddSecondWindow) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	const sf::RenderWindow& window1 = TIE::WindowManager::Instance()->addWindow();
	const sf::RenderWindow& window2 = TIE::WindowManager::Instance()->addWindow();

	ASSERT_TRUE(CheckDebugLogForText(WARN_LEVEL_PREFIX + SECOND_WINDOW_WARNING));

	sf::Vector2u window1Size = window1.getSize();
	sf::Vector2u window2Size(800, 600);
	ASSERT_EQ(window1Size.x, window2Size.x);
	ASSERT_EQ(window1Size.y, window2Size.y);

	const sf::ContextSettings& window1Settings = window1.getSettings();
	const sf::ContextSettings& window2Settings = window2.getSettings();
	ASSERT_EQ(window1Settings.antialiasingLevel, window2Settings.antialiasingLevel);
	ASSERT_EQ(window1Settings.attributeFlags, window2Settings.attributeFlags);
	ASSERT_EQ(window1Settings.Core, window2Settings.Core);
	ASSERT_EQ(window1Settings.Debug, window2Settings.Debug);
	ASSERT_EQ(window1Settings.depthBits, window2Settings.depthBits);
	ASSERT_EQ(window1Settings.stencilBits, window2Settings.stencilBits);

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
	std::string expected = TEST_NONSENSE_1;
	TIE::WindowManager::Instance()->addWindow(sf::VideoMode(800, 600), expected);
	const std::string& actual = TIE::WindowManager::Instance()->getTitle();
	ASSERT_EQ(expected, actual);

	TIE::WindowManager::Instance()->removeWindow();
}

//TEST(WindowManager, ShowFPSInTitle) {}