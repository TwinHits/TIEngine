#include "../pch.h"

#include "../Constants.h"

TEST(StringToInt, StringToInt) {
	int one = TIE::StringToInt(ONE);
	int two = TIE::StringToInt(TWO);
	int three = TIE::StringToInt(THREE);

	ASSERT_EQ(one, 1);
	ASSERT_EQ(two, 2);
	ASSERT_EQ(three, 3);
}