#include "../pch.h"

TEST(Player, CreatePlayer) {
	TIE::GlobalId id = TIE::HashManager::Instance()->getNewGlobalId();
	sf::View& view = TIE::ViewManager::Instance()->getActiveView();
	TIE::Player player(id, view);
	ASSERT_EQ(id, player.getId());
}


TEST(Player, GetId) {
	TIE::GlobalId id = TIE::HashManager::Instance()->getNewGlobalId();
	sf::View& view = TIE::ViewManager::Instance()->getActiveView();
	TIE::Player player(id, view);
	ASSERT_EQ(id, player.getId());
}
