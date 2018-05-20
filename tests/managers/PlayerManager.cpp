#include "../pch.h"

TEST(PlayerManager, AddPlayer) {
	const TIE::Player& player1 = TIE::PlayerManager::Instance()->addPlayer();
	const TIE::Player& player2 = TIE::PlayerManager::Instance()->addPlayer();
	TIE::GlobalId id1 = player1.getId();
	TIE::GlobalId id2 = player2.getId();
	ASSERT_NE(id1, id2);
}


TEST(PlayerManager, GetPlayer) {
	const TIE::Player& addPlayer = TIE::PlayerManager::Instance()->addPlayer();
	TIE::GlobalId addId = addPlayer.getId();
	const TIE::Player& getPlayer = TIE::PlayerManager::Instance()->getPlayer(addId);
	TIE::GlobalId getId = getPlayer.getId();
	ASSERT_EQ(getId, addId);
}


TEST(PlayerManager, GetAllPlayers) {
	const TIE::Player& player3 = TIE::PlayerManager::Instance()->addPlayer();
	const std::map<TIE::GlobalId, std::unique_ptr<TIE::Player> >& players = TIE::PlayerManager::Instance()->getAllPlayers();
	ASSERT_EQ(players.size(), 4);
	for (auto& p : players) {
		ASSERT_TRUE(p.second != nullptr);
	}
}
