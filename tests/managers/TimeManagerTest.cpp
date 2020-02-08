#include "../pch.h"

TEST(TimeManager, AddNewClock) {
	sf::Clock& clock1 = TIE::TimeManager::Instance()->addClock();
	sf::Clock& clock2 = TIE::TimeManager::Instance()->addClock();

	ASSERT_NE(clock1.getElapsedTime(), clock2.getElapsedTime());
}


TEST(TimeManager, GetClock) {
	TIE::GlobalId clockId1 = 12312;
	TIE::GlobalId clockId2 = TIE::HashManager::Instance()->getNewGlobalId();
	TIE::HashManager::Instance()->setSeed(clockId1);
	sf::Clock& clock1 = TIE::TimeManager::Instance()->getClock(clockId1);
	sf::Clock& clock2 = TIE::TimeManager::Instance()->getClock(clockId2);

	ASSERT_NE(clock1.getElapsedTime(), clock2.getElapsedTime());
}
