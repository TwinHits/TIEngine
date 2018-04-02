#include "pch.h"

//Using the Singleton instance method should return the object
TEST(Singleton, Instance) {
	auto singleton = TIE::Singleton<int>::Instance();

	ASSERT_TRUE(singleton != nullptr);
}

//Calling the Singleton instance method twice for the same type should return the same object
TEST(Singleton, MultipleInstances) {
	auto intSingleton1 = TIE::Singleton<int>::Instance();
	auto intSingleton2 = TIE::Singleton<int>::Instance();

	auto charSingleton1 = TIE::Singleton<char>::Instance();
	auto charSingleton2 = TIE::Singleton<char>::Instance();

	ASSERT_EQ(intSingleton1, intSingleton2);
	ASSERT_EQ(charSingleton1, charSingleton2);
}
