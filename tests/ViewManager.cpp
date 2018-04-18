#include "pch.h"

#include "Constants.h"
#include "Helpers.h"

TEST(ViewManager, AddViewDefault) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	TIE::GlobalId viewId = TIE::ViewManager::Instance()->addView();
	TIE::LogManager::Instance()->logDebug(TEST_NONSENSE_2);
	const sf::View& view = TIE::ViewManager::Instance()->getView(viewId);
	ASSERT_FALSE(CheckDebugLogForText(ERROR_LEVEL_PREFIX + NO_VIEW_TO_GET_ERROR));

	sf::Vector2f expectedCenter = DEFAULT_VIEW_CENTER;
	const sf::Vector2f& actualCenter = view.getCenter();
	ASSERT_EQ(expectedCenter.x, actualCenter.x);
	ASSERT_EQ(expectedCenter.y, actualCenter.y);

	sf::Vector2f expectedSize = DEFAULT_VIEW_SIZE;
	const sf::Vector2f& actualSize = view.getSize();
	ASSERT_EQ(expectedSize.x, actualSize.x);
	ASSERT_EQ(expectedSize.y, actualSize.y);

	TIE::ViewManager::Instance()->removeView(viewId);
}


TEST(ViewManager, RemoveView) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	TIE::GlobalId viewId = TIE::ViewManager::Instance()->addView();
	TIE::LogManager::Instance()->logDebug(TEST_NONSENSE_1);

	TIE::ViewManager::Instance()->removeView(viewId);
	ASSERT_FALSE(CheckDebugLogForText(WARN_LEVEL_PREFIX + NO_VIEW_TO_REMOVE_WARNING));

	TIE::ViewManager::Instance()->getView(viewId);
	ASSERT_TRUE(CheckDebugLogForText(ERROR_LEVEL_PREFIX + NO_VIEW_TO_GET_ERROR));
}


TEST(ViewManager, AddViewCustom) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	TIE::GlobalId viewId = TIE::ViewManager::Instance()->addView(CUSTOM_VIEW_RECT);
	TIE::LogManager::Instance()->logDebug(TEST_NONSENSE_3);
	const sf::View& view = TIE::ViewManager::Instance()->getView(viewId);
	ASSERT_FALSE(CheckDebugLogForText(ERROR_LEVEL_PREFIX + NO_VIEW_TO_GET_ERROR));

	sf::Vector2f expectedCenter = CUSTOM_VIEW_CENTER;
	const sf::Vector2f& actualCenter = view.getCenter();
	ASSERT_EQ(expectedCenter.x, actualCenter.x);
	ASSERT_EQ(expectedCenter.y, actualCenter.y);

	sf::Vector2f expectedSize = CUSTOM_VIEW_SIZE;
	const sf::Vector2f& actualSize = view.getSize();
	ASSERT_EQ(expectedSize.x, actualSize.x);
	ASSERT_EQ(expectedSize.y, actualSize.y);

	TIE::ViewManager::Instance()->removeView(viewId);
}


TEST(ViewManager, GetView) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	TIE::GlobalId viewId = TIE::ViewManager::Instance()->addView(CUSTOM_VIEW_RECT);
	TIE::LogManager::Instance()->logDebug(TEST_NONSENSE_1);
	const sf::View& view = TIE::ViewManager::Instance()->getView(viewId);
	ASSERT_FALSE(CheckDebugLogForText(ERROR_LEVEL_PREFIX + NO_VIEW_TO_GET_ERROR));

	sf::Vector2f expectedCenter = CUSTOM_VIEW_CENTER;
	const sf::Vector2f& actualCenter = view.getCenter();
	ASSERT_EQ(expectedCenter.x, actualCenter.x);
	ASSERT_EQ(expectedCenter.y, actualCenter.y);

	sf::Vector2f expectedSize = CUSTOM_VIEW_SIZE;
	const sf::Vector2f& actualSize = view.getSize();
	ASSERT_EQ(expectedSize.x, actualSize.x);
	ASSERT_EQ(expectedSize.y, actualSize.y);

	TIE::ViewManager::Instance()->removeView(viewId);
}


TEST(ViewManager, GetViewDefault) {

	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);
	TIE::LogManager::Instance()->logDebug(TEST_NONSENSE_1);

	const sf::View& view = TIE::ViewManager::Instance()->getView(VIEW_UNUSED_ID);
	ASSERT_TRUE(CheckDebugLogForText(ERROR_LEVEL_PREFIX + NO_VIEW_TO_GET_ERROR));
}


TEST(ViewManager, SetActiveView) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	TIE::GlobalId viewId = TIE::ViewManager::Instance()->addView(CUSTOM_VIEW_RECT);
	const sf::View& expected = TIE::ViewManager::Instance()->getView(viewId);
	TIE::ViewManager::Instance()->setActiveView(viewId);
	const sf::View& actual = TIE::ViewManager::Instance()->getActiveView();

	sf::Vector2f expectedCenter = CUSTOM_VIEW_CENTER;
	const sf::Vector2f& actualCenter =actual.getCenter();
	ASSERT_EQ(expectedCenter.x, actualCenter.x);
	ASSERT_EQ(expectedCenter.y, actualCenter.y);

	sf::Vector2f expectedSize = CUSTOM_VIEW_SIZE;
	const sf::Vector2f& actualSize = actual.getSize();
	ASSERT_EQ(expectedSize.x, actualSize.x);
	ASSERT_EQ(expectedSize.y, actualSize.y);
}


TEST(ViewManager, UpdateCamera) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	const sf::RenderWindow& window = TIE::WindowManager::Instance()->addWindow();
	TIE::GlobalId viewId = TIE::ViewManager::Instance()->addView();
	TIE::ViewManager::Instance()->setActiveView(viewId);
	TIE::ViewManager::Instance()->updateCamera();

	const sf::View& expected = TIE::ViewManager::Instance()->getActiveView();
	const sf::View& actual = window.getView();

	const sf::Vector2f& expectedCenter = expected.getCenter();
	const sf::Vector2f& actualCenter = actual.getCenter();
	ASSERT_EQ(expectedCenter.x, actualCenter.x);
	ASSERT_EQ(expectedCenter.y, actualCenter.y);

	const sf::Vector2f& expectedSize = expected.getSize();
	const sf::Vector2f& actualSize = actual.getSize();
	ASSERT_EQ(expectedSize.x, actualSize.x);
	ASSERT_EQ(expectedSize.y, actualSize.y);

	TIE::WindowManager::Instance()->removeWindow();
	TIE::ViewManager::Instance()->removeView(viewId);
}


TEST(ViewManager, Scroll) {

	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	const sf::RenderWindow& window = TIE::WindowManager::Instance()->addWindow();
	TIE::GlobalId viewId = TIE::ViewManager::Instance()->addView();
	TIE::ViewManager::Instance()->setActiveView(viewId);
	const sf::View& view = TIE::ViewManager::Instance()->getActiveView();

	const sf::Vector2f expectedNeutralScroll = sf::Vector2f(0, 0);
	const sf::Vector2f actualNeutralScroll = view.getCenter();
	ASSERT_EQ(expectedNeutralScroll.x, actualNeutralScroll.x);
	ASSERT_EQ(expectedNeutralScroll.y, actualNeutralScroll.y);

	TIE::ViewManager::Instance()->scroll(TIE::Direction::TOP);
	const sf::Vector2f expectedTopScroll = sf::Vector2f(0, -SCROLL_SPEED);
	const sf::Vector2f actualTopScroll = view.getCenter();
	ASSERT_EQ(expectedTopScroll.x, actualTopScroll.x);
	ASSERT_EQ(expectedTopScroll.y, actualTopScroll.y);

	TIE::ViewManager::Instance()->scroll(TIE::Direction::RIGHT);
	const sf::Vector2f expectedRightScroll = sf::Vector2f(SCROLL_SPEED, -SCROLL_SPEED);
	const sf::Vector2f actualRightScroll = view.getCenter();
	ASSERT_EQ(expectedRightScroll.x, actualRightScroll.x);
	ASSERT_EQ(expectedRightScroll.y, actualRightScroll.y);

	TIE::ViewManager::Instance()->scroll(TIE::Direction::BOTTOM);
	const sf::Vector2f expectedBottomScroll = sf::Vector2f(SCROLL_SPEED, 0);
	const sf::Vector2f actualBottomScroll = view.getCenter();
	ASSERT_EQ(expectedBottomScroll.x, actualBottomScroll.x);
	ASSERT_EQ(expectedBottomScroll.y, actualBottomScroll.y);

	TIE::ViewManager::Instance()->scroll(TIE::Direction::LEFT);
	const sf::Vector2f expectedLeftScroll = sf::Vector2f(0, 0);
	const sf::Vector2f actualLeftScroll = view.getCenter();
	ASSERT_EQ(expectedLeftScroll.x, actualLeftScroll.x);
	ASSERT_EQ(expectedLeftScroll.y, actualLeftScroll.y);
}


//TEST(ViewManager, Zoom) {}