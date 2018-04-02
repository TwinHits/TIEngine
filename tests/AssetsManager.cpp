#include "pch.h"

//Using the Singletone instance method should return the object
TEST(AssetsManager, GetInstance_NotNull) {
	const TIE::AssetsManager* assetsManager = TIE::AssetsManager::Instance();

	ASSERT_TRUE(assetsManager != nullptr);
}

//Calling the Singleton instance method twice should return the same object
TEST(AssetsManager, GetInstanceTwice_SameInstance) {
	const TIE::AssetsManager* assetsManager1 = TIE::AssetsManager::Instance();
	const TIE::AssetsManager* assetsManager2 = TIE::AssetsManager::Instance();

	ASSERT_EQ(assetsManager1, assetsManager2);
}
