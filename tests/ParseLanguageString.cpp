#include "pch.h"

#include "Constants.h"

TEST(ParseLanguageString, ValidInput) {
	ASSERT_EQ(TIE::Language::en_US, TIE::parseLanguageString(EN_STRING));	
	ASSERT_EQ(TIE::Language::es_ES, TIE::parseLanguageString(ES_STRING));	
	ASSERT_EQ(TIE::Language::fe_FR, TIE::parseLanguageString(FR_STRING));	
	ASSERT_EQ(TIE::Language::de_DE, TIE::parseLanguageString(DE_STRING));	
	ASSERT_EQ(TIE::Language::ja_JP, TIE::parseLanguageString(JA_STRING));	
}

TEST(ParseLanguageString, InvalidInput) {
	ASSERT_EQ(TIE::Language::en_US, TIE::parseLanguageString(TEST_NONSENSE_1));	
	ASSERT_EQ(TIE::Language::en_US, TIE::parseLanguageString(TEST_NONSENSE_2));	
	ASSERT_EQ(TIE::Language::en_US, TIE::parseLanguageString(TEST_NONSENSE_3));	
	ASSERT_EQ(TIE::Language::en_US, TIE::parseLanguageString(TEST_NONSENSE_4));	
}
