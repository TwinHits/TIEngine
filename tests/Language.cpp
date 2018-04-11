#include "pch.h"

//Just check and make sure that each int casts to a TIE::Language correctly
TEST(Language, IntToLanguage) {
	int languageAsInt = 0;
	ASSERT_EQ(languageAsInt, TIE::en_US);

	++languageAsInt;
	ASSERT_EQ(languageAsInt, TIE::fe_FR);

	++languageAsInt;
	ASSERT_EQ(languageAsInt, TIE::es_ES);

	++languageAsInt;
	ASSERT_EQ(languageAsInt, TIE::de_DE);

	++languageAsInt;
	ASSERT_EQ(languageAsInt, TIE::ja_JP);
}