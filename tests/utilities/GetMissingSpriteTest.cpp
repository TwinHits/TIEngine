#include "../pch.h"

#include "../Constants.h"

TEST(MissingSprite, GetMissingSprite) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);

	sf::Sprite missingSprite = TIE::getMissingSprite();
	
	ASSERT_EQ(missingSprite.getOrigin(), TIE::MISSING_SPRITE_ORIGIN);
	ASSERT_EQ(missingSprite.getPosition(), TIE::MISSING_SPRITE_POSITION);
	ASSERT_EQ(missingSprite.getScale(), TIE::MISSING_SPRITE_SCALE);
	ASSERT_EQ(missingSprite.getTextureRect(), TIE::MISSING_SPRITE_SIZE);
}
