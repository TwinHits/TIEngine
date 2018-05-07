#include "../pch.h"

#include "../Constants.h"

TEST(ParseLanguageString, ValidInput) {
	ASSERT_EQ(TIE::Language::en_US, TIE::parseLanguageString(TIE::EN_STRING));	
	ASSERT_EQ(TIE::Language::es_ES, TIE::parseLanguageString(TIE::ES_STRING));	
	ASSERT_EQ(TIE::Language::fe_FR, TIE::parseLanguageString(TIE::FR_STRING));	
	ASSERT_EQ(TIE::Language::de_DE, TIE::parseLanguageString(TIE::DE_STRING));	
	ASSERT_EQ(TIE::Language::ja_JP, TIE::parseLanguageString(TIE::JA_STRING));	
}

TEST(ParseLanguageString, InvalidInput) {
	ASSERT_EQ(TIE::Language::en_US, TIE::parseLanguageString(TIE::TEST_NONSENSE_1));	
	ASSERT_EQ(TIE::Language::en_US, TIE::parseLanguageString(TIE::TEST_NONSENSE_2));	
	ASSERT_EQ(TIE::Language::en_US, TIE::parseLanguageString(TIE::TEST_NONSENSE_3));	
	ASSERT_EQ(TIE::Language::en_US, TIE::parseLanguageString(TIE::TEST_NONSENSE_4));	
}
