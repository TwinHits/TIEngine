#include "../pch.h"

#include "../Constants.h"

TEST(MissingSprite, GetMissingSprite) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	sf::Sprite missingSprite = TIE::getMissingSprite();
	
	ASSERT_EQ(missingSprite.getOrigin(), MISSING_SPRITE_ORIGIN);
	ASSERT_EQ(missingSprite.getPosition(), MISSING_SPRITE_POSITION);
	ASSERT_EQ(missingSprite.getScale(), MISSING_SPRITE_SCALE);
	ASSERT_EQ(missingSprite.getTextureRect(), MISSING_SPRITE_SIZE);
}