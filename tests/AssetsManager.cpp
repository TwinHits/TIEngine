#include "pch.h"

std::string TEST_CONFIG_FILE = "../../tests/testconfig.ini";
std::string TEST_TEXTURE = "test_texture.png";
int TEST_TEXTURE_SIZE_X = 256;
int DEFAULT_TEXTURE_SIZE_X = 512;
std::string TEST_FONT = "test_font.ttf";
std::string TEST_FONT_FAMILY = "Oswald Regular";
std::string DEFAULT_FONT_FAMILY = "";
std::string TEST_AUDIO = "test_audio";
std::string TEST_NONSENSE = "memes";

//Test that private method ParseAssets successfully parses all assets. This will runtime_exception if it fails.
TEST(AssetsManager, ParseAssets) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);
	TIE::AssetsManager::Instance();
}

//Using known texture name, make sure that missing_texture is not returned
TEST(AssetsManager, GetTextureByName) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);
	const sf::Texture& texture = TIE::AssetsManager::Instance()->getTexture(TEST_TEXTURE);
	//sf::Texture has no comparison operator, but we're looking for a 256 sized texture and the missing_texture is 512.
	ASSERT_EQ(texture.getSize().x, 256);
}

//Using a known texture name, make a hash and get the sf::texture by hashed id
TEST(AssetsManager, GetTextureById) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);
	GlobalId hashedTextureId = TIE::HashManager::Instance()->getHash(TEST_TEXTURE);
	const sf::Texture& texture = TIE::AssetsManager::Instance()->getTexture(hashedTextureId);
	//sf::Texture has no comparison operator, but we're looking for a 256 sized texture and the missing_texture is 512.
	ASSERT_EQ(texture.getSize().x, 256);
}

//When given an invalid texture id, the missing_texture should be returned
TEST(AssetsManager, GetDefaultTexture) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);
	const sf::Texture& texture = TIE::AssetsManager::Instance()->getTexture(TEST_NONSENSE);
	//sf::Texture has no comparison operator, but missing_texture's x is 512.
	ASSERT_EQ(texture.getSize().x, DEFAULT_TEXTURE_SIZE_X);
}

//Using a known font name, get the sf::font
TEST(AssetsManager, GetFontByName) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);
	const sf::Font& success = TIE::AssetsManager::Instance()->getFont(TEST_FONT);
	const sf::Font& failure = TIE::AssetsManager::Instance()->getFont(TEST_NONSENSE);

	//sf::Font have no comparison operators, but the font has a distinctive font family
	ASSERT_EQ(success.getInfo().family, TEST_FONT_FAMILY);
	ASSERT_NE(success.getInfo().family, failure.getInfo().family);
}

//Using a known font name, make a hash and get the sf::font by hashed id
TEST(AssetsManager, GetFontById) {
	GlobalId hashedfont = TIE::HashManager::Instance()->getHash(TEST_FONT);
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);
	const sf::Font& success = TIE::AssetsManager::Instance()->getFont(hashedfont);
	const sf::Font& failure = TIE::AssetsManager::Instance()->getFont(TEST_NONSENSE);

	//sf::Font have no comparison operators, but the text texture has a distinctive font family
	ASSERT_EQ(success.getInfo().family, TEST_FONT_FAMILY);
	ASSERT_NE(success.getInfo().family, failure.getInfo().family);
}

//When given an invalid font id, the default font should be returned
TEST(AssetsManager, GetDefaultFont) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);
	const sf::Font& font = TIE::AssetsManager::Instance()->getFont(TEST_NONSENSE);
	//sf::Font has no comparison operator, but missing_font's family 
	ASSERT_EQ(font.getInfo().family, DEFAULT_FONT_FAMILY);
}

TEST(AssetsManager, GetAudioByName) {
	
}

TEST(AssetsManager, GetAudioById) {

}

TEST(AssetsManager, GetDefaultAudio) {

}