#include "../pch.h"

#include "../Constants.h"

TEST(MissingText, GetMissingText) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);

	sf::Text missingText = TIE::getMissingText();

	ASSERT_EQ(missingText.getFont()->getInfo().family, TIE::AssetsManager::Instance()->getFont(TIE::MISSING_TEXT_FONT).getInfo().family);
	ASSERT_EQ(missingText.getString(), TIE::MISSING_TEXT_STRING);
	ASSERT_EQ(missingText.getPosition(), TIE::MISSING_TEXT_POSITION);
	ASSERT_EQ(missingText.getCharacterSize(), TIE::MISSING_TEXT_CHARACTER_SIZE);
}
