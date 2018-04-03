#include "pch.h"

//Get a new unique global id
TEST(HashManager, GetNewGlobalId) {
	GlobalId id1 = TIE::HashManager::Instance()->getNewGlobalId();
	GlobalId id2 = TIE::HashManager::Instance()->getNewGlobalId();
	GlobalId id3 = TIE::HashManager::Instance()->getNewGlobalId();

	ASSERT_EQ(id1, 1);
	ASSERT_EQ(id2, 2);
	ASSERT_EQ(id3, 3);
}

//Set the seed for the global id and get new ids
TEST(HashManager, SetGlobalIdSeed) {
	TIE::HashManager::Instance()->setSeed(123456);
	GlobalId id1 = TIE::HashManager::Instance()->getNewGlobalId();
	GlobalId id2 = TIE::HashManager::Instance()->getNewGlobalId();
	GlobalId id3 = TIE::HashManager::Instance()->getNewGlobalId();

	ASSERT_EQ(id1, 123457);
	ASSERT_EQ(id2, 123458);
	ASSERT_EQ(id3, 123459);
}

//Get the hashed values for three nonsense objects and make sure they aren't the same or are
TEST(HashManager, GetHashForObject) {
	std::string nonsense1 = "My fair lady reinforces gender sterotypes";
	std::string nonsense2 = "memes are the DNA of the soul";
	std::string nonsense3 = "the non gender specific pronoun's revenage";

	GlobalId id1 = TIE::HashManager::Instance()->getHash(nonsense1);
	GlobalId id2 = TIE::HashManager::Instance()->getHash(nonsense2);
	GlobalId id3 = TIE::HashManager::Instance()->getHash(nonsense3);

	ASSERT_NE(id1, id2);
	ASSERT_NE(id2, id3);
	ASSERT_NE(id3, id1); 

	GlobalId id4 = TIE::HashManager::Instance()->getHash(nonsense1);
	GlobalId id5 = TIE::HashManager::Instance()->getHash(nonsense2);
	GlobalId id6 = TIE::HashManager::Instance()->getHash(nonsense3);

	ASSERT_EQ(id1, id4);
	ASSERT_EQ(id2, id5);
	ASSERT_EQ(id3, id6); 
}