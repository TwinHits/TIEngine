#include "pch.h"

//Using the Singleton instance method should return the object
TEST(Singleton, Instance) {
	const TIE::ConfigManager* configManager = TIE::ConfigManager::Instance();

	ASSERT_TRUE(configManager != nullptr);
}

//Calling the Singleton instance method twice should return the same object
TEST(Singleton, MultipleInstances) {
	const TIE::ConfigManager* configManager1 = TIE::ConfigManager::Instance();
	const TIE::ConfigManager* configManager2 = TIE::ConfigManager::Instance();

	ASSERT_EQ(configManager1, configManager2);
}
