#include "pch.h"
#include <climits>

TEST(GlobalId, GlobalIdIsAnUnsignedLong) {
	TIE::GlobalId max = ULONG_MAX;
	TIE::GlobalId min = 0;
	TIE::GlobalId neg = LONG_MIN;
	TIE::GlobalId pos = LONG_MAX;
	ASSERT_EQ(max, ULONG_MAX);
	ASSERT_EQ(min, 0);
	ASSERT_EQ(neg, pos);
}
