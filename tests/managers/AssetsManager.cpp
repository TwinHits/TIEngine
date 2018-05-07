#include "../pch.h"

#include "../Constants.h"

//Test that private method ParseAssets successfully parses all assets. This will runtime_exception if it fails.
TEST(AssetsManager, ParseAssets) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);
	TIE::AssetsManager::Instance();
}

//Using known texture name, make sure that missing_texture is not returned
TEST(AssetsManager, GetTextureByName) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);
	const sf::Texture& texture = TIE::AssetsManager::Instance()->getTexture(TIE::TEST_TEXTURE);
	//sf::Texture has no comparison operator, but we're looking for a 256 sized texture and the missing_texture is 512.
	ASSERT_EQ(texture.getSize().x, TIE::TEST_TEXTURE_SIZE_X);
}

//Using a known texture name, make a hash and get the sf::texture by hashed id
TEST(AssetsManager, GetTextureById) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);
	TIE::GlobalId hashedTextureId = TIE::HashManager::Instance()->getHash(TIE::TEST_TEXTURE);
	const sf::Texture& texture = TIE::AssetsManager::Instance()->getTexture(hashedTextureId);
	//sf::Texture has no comparison operator, but we're looking for a 256 sized texture and the missing_texture is 512.
	ASSERT_EQ(texture.getSize().x, TIE::TEST_TEXTURE_SIZE_X);
}

//When given an invalid texture id, the missing_texture should be returned
TEST(AssetsManager, GetDefaultTexture) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);
	const sf::Texture& texture = TIE::AssetsManager::Instance()->getTexture(TIE::TEST_NONSENSE_1);
	//sf::Texture has no comparison operator, but missing_texture's x is 512.
	ASSERT_EQ(texture.getSize().x, TIE::DEFAULT_TEXTURE_SIZE_X);
}

//Using a known font name, get the sf::font
TEST(AssetsManager, GetFontByName) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);
	const sf::Font& success = TIE::AssetsManager::Instance()->getFont(TIE::TEST_FONT);
	const sf::Font& failure = TIE::AssetsManager::Instance()->getFont(TIE::TEST_NONSENSE_1);

	//sf::Font have no comparison operators, but the font has a distinctive font family
	ASSERT_EQ(success.getInfo().family, TIE::TEST_FONT_FAMILY);
	ASSERT_NE(success.getInfo().family, failure.getInfo().family);
}

//Using a known font name, make a hash and get the sf::font by hashed id
TEST(AssetsManager, GetFontById) {
	TIE::GlobalId hashedfont = TIE::HashManager::Instance()->getHash(TIE::TEST_FONT);
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);
	const sf::Font& success = TIE::AssetsManager::Instance()->getFont(hashedfont);
	const sf::Font& failure = TIE::AssetsManager::Instance()->getFont(TIE::TEST_NONSENSE_1);

	//sf::Font have no comparison operators, but the text texture has a distinctive font family
	ASSERT_EQ(success.getInfo().family, TIE::TEST_FONT_FAMILY);
	ASSERT_NE(success.getInfo().family, failure.getInfo().family);
}

//When given an invalid font id, the default font should be returned
TEST(AssetsManager, GetDefaultFont) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);
	const sf::Font& font = TIE::AssetsManager::Instance()->getFont(TIE::TEST_NONSENSE_1);
	//sf::Font has no comparison operator, but missing_font's family 
	ASSERT_EQ(font.getInfo().family, TIE::DEFAULT_FONT_FAMILY);
}

TEST(AssetsManager, GetAudioByName) {
	
}

TEST(AssetsManager, GetAudioById) {

}

TEST(AssetsManager, GetDefaultAudio) {

}