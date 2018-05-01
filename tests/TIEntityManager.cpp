#include "pch.h"

#include "Constants.h"
#include "Helpers.h"

TEST(TIEntityManager, AddTIEntity) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	std::unique_ptr<TIE::TIEntity> entity = TIE::make_unique<TIE::TIEntity>();
	TIE::GlobalId expected = entity->getId();
	TIE::TIEntityManager::Instance()->addTIEntity(std::move(entity));

	const TIE::TIEntity& entity2 = TIE::TIEntityManager::Instance()->getTIEntity(expected);
	TIE::GlobalId actual = entity2.getId();

	ASSERT_EQ(actual, expected);
}


TEST(TIEntityManager, RemoveTIEntity) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	std::unique_ptr<TIE::TIEntity> entity = TIE::make_unique<TIE::TIEntity>();
	TIE::GlobalId id = entity->getId();
	TIE::TIEntityManager::Instance()->addTIEntity(std::move(entity));

	TIE::LogManager::Instance()->logDebug(TEST_NONSENSE_1);
	TIE::TIEntityManager::Instance()->removeTIEntity(id);

	ASSERT_TRUE(CheckDebugLogForText(DELETED_TIENTITY_INFO + std::to_string(id)));
}


TEST(TIEntityManager, AddSceneText) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	std::unique_ptr<TIE::SceneText> text = TIE::make_unique<TIE::SceneText>();
	TIE::GlobalId expected = text->getId();
	TIE::TIEntityManager::Instance()->addSceneText(std::move(text));

	const TIE::SceneText& text2 = TIE::TIEntityManager::Instance()->getSceneText(expected);
	TIE::GlobalId actual = text2.getId();

	ASSERT_EQ(actual, expected);
}


TEST(TIEntityManager, RemoveSceneText) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	std::unique_ptr<TIE::SceneText> text = TIE::make_unique<TIE::SceneText>();
	TIE::GlobalId id = text->getId();
	TIE::TIEntityManager::Instance()->addSceneText(std::move(text));

	TIE::LogManager::Instance()->logDebug(TEST_NONSENSE_1);
	TIE::TIEntityManager::Instance()->removeSceneText(id);

	ASSERT_TRUE(CheckDebugLogForText(DELETED_SCENETEXT_INFO + std::to_string(id)));
}


TEST(TIEntityManager, GetTIEntity) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	std::unique_ptr<TIE::TIEntity> entity1 = TIE::make_unique<TIE::TIEntity>();
	TIE::GlobalId id1 = entity1->getId();
	TIE::TIEntityManager::Instance()->addTIEntity(std::move(entity1));

	std::unique_ptr<TIE::TIEntity> entity2 = TIE::make_unique<TIE::TIEntity>();
	TIE::GlobalId id2 = entity2->getId();
	TIE::TIEntityManager::Instance()->addTIEntity(std::move(entity2));

	const TIE::TIEntity& actual1 = TIE::TIEntityManager::Instance()->getTIEntity(id1);
	const TIE::TIEntity& actual2 = TIE::TIEntityManager::Instance()->getTIEntity(id2);

	ASSERT_EQ(id1, actual1.getId());
	ASSERT_EQ(id2, actual2.getId());
}


TEST(TIEntityManager, GetAllTIEntities) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);
	
	std::unique_ptr<TIE::TIEntity> entity1 = TIE::make_unique<TIE::TIEntity>();
	TIE::GlobalId id1 = entity1->getId();
	TIE::TIEntityManager::Instance()->addTIEntity(std::move(entity1));

	std::unique_ptr<TIE::TIEntity> entity2 = TIE::make_unique<TIE::TIEntity>();
	TIE::GlobalId id2 = entity2->getId();
	TIE::TIEntityManager::Instance()->addTIEntity(std::move(entity2));

	std::unique_ptr<TIE::TIEntity> entity3 = TIE::make_unique<TIE::TIEntity>();
	TIE::GlobalId id3 = entity3->getId();
	TIE::TIEntityManager::Instance()->addTIEntity(std::move(entity3));

	const std::map<TIE::GlobalId, std::unique_ptr<TIE::TIEntity> >& entities = TIE::TIEntityManager::Instance()->getAllTIEntitys();

	ASSERT_EQ(entities.at(id1)->getId(), id1);
	ASSERT_EQ(entities.at(id2)->getId(), id2);
	ASSERT_EQ(entities.at(id3)->getId(), id3);
}


TEST(TIEntityManager, GetSceneText) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	std::unique_ptr<TIE::SceneText> text1 = TIE::make_unique<TIE::SceneText>();
	TIE::GlobalId id1 = text1->getId();
	TIE::TIEntityManager::Instance()->addSceneText(std::move(text1));
	
	std::unique_ptr<TIE::SceneText> text2 = TIE::make_unique<TIE::SceneText>();
	TIE::GlobalId id2 = text2->getId();
	TIE::TIEntityManager::Instance()->addSceneText(std::move(text2));

	const TIE::SceneText& actual1 = TIE::TIEntityManager::Instance()->getSceneText(id1);
	const TIE::SceneText& actual2 = TIE::TIEntityManager::Instance()->getSceneText(id2);

	ASSERT_EQ(id1, actual1.getId());
	ASSERT_EQ(id2, actual2.getId());
}


TEST(TIEntityManager, GetAllSceneTexts) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	std::unique_ptr<TIE::SceneText> text1 = TIE::make_unique<TIE::SceneText>();
	TIE::GlobalId id1 = text1->getId();
	TIE::TIEntityManager::Instance()->addSceneText(std::move(text1));

	std::unique_ptr<TIE::SceneText> text2 = TIE::make_unique<TIE::SceneText>();
	TIE::GlobalId id2 = text2->getId();
	TIE::TIEntityManager::Instance()->addSceneText(std::move(text2));

	std::unique_ptr<TIE::SceneText> text3 = TIE::make_unique<TIE::SceneText>();
	TIE::GlobalId id3 = text3->getId();
	TIE::TIEntityManager::Instance()->addSceneText(std::move(text3));

	const std::map<TIE::GlobalId, std::unique_ptr<TIE::SceneText> >& texts = TIE::TIEntityManager::Instance()->getAllSceneTexts();

	ASSERT_EQ(texts.at(id1)->getId(), id1);
	ASSERT_EQ(texts.at(id2)->getId(), id2);
	ASSERT_EQ(texts.at(id3)->getId(), id3);
}


//TEST(TIEntityManager, UpdateGameState) {}
