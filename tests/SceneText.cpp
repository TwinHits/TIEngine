#include "pch.h"

#include "Constants.h"

TEST(SceneText, GetId) {
	TIE::HashManager::Instance()->setSeed(SCENETEXT_UNUSED_ID);
	//plus 2 for the clock initialized inside the constructor	
	TIE::GlobalId expected = SCENETEXT_UNUSED_ID + 2;
	TIE::SceneText sceneText = TIE::SceneText();
	TIE::GlobalId actual = sceneText.getId();

	ASSERT_EQ(expected, actual);
}


TEST(SceneText, GetText) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);
	TIE::SceneText text = TIE::SceneText();

	sf::Text expected = TIE::getMissingText();
	sf::Text& actual = text.getText();
	
	ASSERT_EQ(expected.getString(), actual.getString());
	ASSERT_EQ(expected.getFont(), actual.getFont());
	ASSERT_EQ(expected.getCharacterSize(), actual.getCharacterSize());
	ASSERT_EQ(expected.getPosition(), actual.getPosition());
}


TEST(SceneText, SetText) {
	TIE::SceneText text = TIE::SceneText();

	sf::Text expected = sf::Text();
	expected.setString(TEST_NONSENSE_1);
	expected.setFont(TIE::AssetsManager::Instance()->getFont(TEST_FONT));
	expected.setCharacterSize(20);
	expected.setPosition(100, 100);

	text.setText(expected);
	sf::Text& actual = text.getText();

	ASSERT_EQ(expected.getString(), actual.getString());
	ASSERT_EQ(expected.getFont(), actual.getFont());
	ASSERT_EQ(expected.getCharacterSize(), actual.getCharacterSize());
	ASSERT_EQ(expected.getPosition(), actual.getPosition());
}


TEST(SceneText, GetDraw) {
	TIE::SceneText sceneText = TIE::SceneText();
	bool expected = DEFAULT_DRAW_BOOL;

	bool actual = sceneText.getDraw();

	ASSERT_EQ(expected, actual);
}


TEST(SceneText, SetDraw) {
	TIE::SceneText sceneText = TIE::SceneText();
	bool expected = CUSTOM_DRAW_BOOL;

	sceneText.setDraw(CUSTOM_DRAW_BOOL);
	bool actual = sceneText.getDraw();

	ASSERT_EQ(expected, actual);
}


TEST(SceneText, EqualToOperator) {
	TIE::SceneText sceneText1 = TIE::SceneText();
	TIE::SceneText sceneText2 = TIE::SceneText();

	ASSERT_EQ(sceneText1, sceneText1);
	ASSERT_EQ(sceneText2, sceneText2);
}


TEST(SceneText, NotEqualToOperator) {
	TIE::SceneText sceneText1 = TIE::SceneText();
	TIE::SceneText sceneText2 = TIE::SceneText();

	ASSERT_NE(sceneText1, sceneText2);
}


TEST(SceneText, AssignmentOperator) {
	TIE::SceneText sceneText1 = TIE::SceneText();
	TIE::SceneText sceneText2 = TIE::SceneText();

	sceneText1 = sceneText2;
	ASSERT_NE(sceneText1, sceneText2);
}


//TEST(SceneText, Update) {}


//TEST(SceneText, RecieveMessage) {}