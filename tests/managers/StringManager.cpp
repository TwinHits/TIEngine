#include "../pch.h"

#include "../Constants.h"

TEST(StringManager, GetDisplayLanguage) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);
	TIE::Language expected = TIE::ConfigManager::Instance()->getDefaultDisplayLanguage();
	TIE::Language actual = TIE::StringManager::Instance()->getDisplayLanguage();

	ASSERT_EQ(expected, actual);
}


TEST(StringManager, SetDisplayLanguage) {
	TIE::Language notExpected = TIE::StringManager::Instance()->getDisplayLanguage();
	TIE::Language expected = TIE::de_DE;
	TIE::StringManager::Instance()->setDisplayLanguage(expected);
	TIE::Language actual = TIE::StringManager::Instance()->getDisplayLanguage();

	ASSERT_NE(notExpected, actual);
	ASSERT_EQ(expected, actual);
}


TEST(StringManager, GetStringForDisplayLanguage) {
	TIE::StringManager::Instance()->setDisplayLanguage(TIE::en_US);
	std::string expected = TIE::TWIN_ION_ENGINE_EN;
	std::string actual = TIE::StringManager::Instance()->getString(TIE::TWIN_ION_ENGINE_ID);
	ASSERT_EQ(expected, actual);
}


TEST(StringManager, GetStringForLangauge) {
	std::string expected = TIE::TWIN_ION_ENGINE_JP;
	std::string actual = TIE::StringManager::Instance()->getString(TIE::TWIN_ION_ENGINE_ID, TIE::ja_JP);
	ASSERT_EQ(expected, actual);
}
