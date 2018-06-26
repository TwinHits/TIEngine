#include "../../pch.h"

#include "../../Constants.h"

TEST(TIExt, GetText) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);
	TIE::TIExt text = TIE::TIExt();

	sf::Text expected = TIE::getMissingText();
	sf::Text& actual = text.getText();
	
	ASSERT_EQ(expected.getString(), actual.getString());
	ASSERT_EQ(expected.getFont(), actual.getFont());
	ASSERT_EQ(expected.getCharacterSize(), actual.getCharacterSize());
	ASSERT_EQ(expected.getPosition(), actual.getPosition());
}


TEST(TIExt, SetText) {
	TIE::TIExt text = TIE::TIExt();

	sf::Text expected = sf::Text();
	expected.setString(TIE::TEST_NONSENSE_1);
	expected.setFont(TIE::AssetsManager::Instance()->getFont(TIE::TEST_FONT));
	expected.setCharacterSize(20);
	expected.setPosition(100, 100);

	text.setText(expected);
	sf::Text& actual = text.getText();

	ASSERT_EQ(expected.getString(), actual.getString());
	ASSERT_EQ(expected.getFont(), actual.getFont());
	ASSERT_EQ(expected.getCharacterSize(), actual.getCharacterSize());
	ASSERT_EQ(expected.getPosition(), actual.getPosition());
}


TEST(TIExt, EqualToOperator) {
	TIE::TIExt sceneText1 = TIE::TIExt();
	TIE::TIExt sceneText2 = TIE::TIExt();

	ASSERT_EQ(sceneText1, sceneText1);
	ASSERT_EQ(sceneText2, sceneText2);
}


TEST(TIExt, NotEqualToOperator) {
	TIE::TIExt sceneText1 = TIE::TIExt();
	TIE::TIExt sceneText2 = TIE::TIExt();

	ASSERT_NE(sceneText1, sceneText2);
}


TEST(TIExt, AssignmentOperator) {
	TIE::TIExt sceneText1 = TIE::TIExt();
	TIE::TIExt sceneText2 = TIE::TIExt();

	sceneText1 = sceneText2;
	ASSERT_NE(sceneText1, sceneText2);
}
