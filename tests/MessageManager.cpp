#include "pch.h"

#include "Constants.h"

TEST(MessageManager, SendMessage) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	std::unique_ptr<TIE::TIEntity> entity1 = TIE::make_unique<TIE::TIEntity>();
	TIE::GlobalId id1 = entity1->getId();
	TIE::TIEntityManager::Instance()->addTIEntity(std::move(entity1));

	std::unique_ptr<TIE::TIEntity> entity2 = TIE::make_unique<TIE::TIEntity>();
	TIE::GlobalId id2 = entity2->getId();
	TIE::TIEntityManager::Instance()->addTIEntity(std::move(entity2));

	TIE::Message message = TIE::Message(id1, id2);
	TIE::MessageManager::Instance()->sendMessage(message);
}
