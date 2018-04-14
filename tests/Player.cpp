#include "pch.h"

TEST(Player, CreatePlayer) {
	TIE::GlobalId id = TIE::HashManager::Instance()->getNewGlobalId();
	TIE::Player player = TIE::Player(id);
	ASSERT_EQ(id, player.getId());
}


TEST(Player, GetId) {
	TIE::GlobalId id = TIE::HashManager::Instance()->getNewGlobalId();
	TIE::Player player = TIE::Player(id);
	ASSERT_EQ(id, player.getId());
}