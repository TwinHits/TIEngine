#include "pch.h"

TEST(LocalTime, LocalTime) {
	std::string time1 = TIE::LocalTime();
	ASSERT_NE(time1, "");
}