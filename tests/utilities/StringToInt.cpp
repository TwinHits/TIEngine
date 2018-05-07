#include "../pch.h"

#include "../Constants.h"

TEST(StringToInt, StringToInt) {
	int one = TIE::StringToInt(TIE::ONE);
	int two = TIE::StringToInt(TIE::TWO);
	int three = TIE::StringToInt(TIE::THREE);

	ASSERT_EQ(one, 1);
	ASSERT_EQ(two, 2);
	ASSERT_EQ(three, 3);
}