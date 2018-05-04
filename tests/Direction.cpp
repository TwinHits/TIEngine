#include "pch.h"

//Just check and make sure that each int casts to a TIE::Language correctly
TEST(Direction, IntToDirection) {
	int languageAsInt = 0;
	ASSERT_EQ(languageAsInt, TIE::TOP);

	++languageAsInt;
	ASSERT_EQ(languageAsInt, TIE::RIGHT);

	++languageAsInt;
	ASSERT_EQ(languageAsInt, TIE::BOTTOM);

	++languageAsInt;
	ASSERT_EQ(languageAsInt, TIE::LEFT);
}
