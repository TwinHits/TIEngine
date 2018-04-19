#include "pch.h"

#include "Constants.h"

TEST(TIEntity, GetId) {
	TIE::HashManager::Instance()->setSeed(ENTITY_UNUSED_ID);
	//plus 2 for the clock initialized inside the constructor	
	TIE::GlobalId expected = ENTITY_UNUSED_ID+2;
	TIE::TIEntity entity = TIE::TIEntity();
	TIE::GlobalId actual = entity.getId();

	ASSERT_EQ(expected, actual);
}


TEST(TIEntity, GetDraw) {
	TIE::TIEntity entity = TIE::TIEntity();
	bool expected = DEFAULT_DRAW_BOOL;

	bool actual = entity.getDraw();

	ASSERT_EQ(expected, actual);
}


TEST(TIEntity, SetDraw) {
	TIE::TIEntity entity = TIE::TIEntity();
	bool expected = CUSTOM_DRAW_BOOL;

	entity.setDraw(CUSTOM_DRAW_BOOL);
	bool actual = entity.getDraw();

	ASSERT_EQ(expected, actual);
}


TEST(TIEntity, GetDrawOrder) {
	TIE::TIEntity entity = TIE::TIEntity();
	int expected = DEFAULT_DRAW_ORDER_INT;

	int actual = entity.getDrawOrder();

	ASSERT_EQ(expected, actual);
}


TEST(TIEntity, SetDrawOrder) {
	TIE::TIEntity entity = TIE::TIEntity();
	int expected = CUSTOM_DRAW_ORDER_INT;

	entity.setDrawOrder(CUSTOM_DRAW_ORDER_INT);
	int actual = entity.getDrawOrder();

	ASSERT_EQ(expected, actual);
}


TEST(TIEntity, GetSprite) {
	TIE::ConfigManager::Instance()->loadConfigFile(TEST_CONFIG_FILE);

	TIE::TIEntity entity = TIE::TIEntity();
	sf::Sprite expected = TIE::getMissingSprite();
	const sf::Sprite& actual = entity.getSprite();

	ASSERT_EQ(expected.getTexture(), actual.getTexture());
	ASSERT_EQ(expected.getScale(), actual.getScale());
	ASSERT_EQ(expected.getOrigin(), actual.getOrigin());
	ASSERT_EQ(expected.getPosition(), actual.getPosition());

	sf::IntRect expectedRect = expected.getTextureRect();
	sf::IntRect actualRect = actual.getTextureRect();
	ASSERT_EQ(expectedRect.left, actualRect.left);
	ASSERT_EQ(expectedRect.top, actualRect.top);
	ASSERT_EQ(expectedRect.height, actualRect.height);
	ASSERT_EQ(expectedRect.width, actualRect.width);
}


TEST(TIEntity, SetSprite) {
	//confirm that setting a new sprite updates the sprite returned by getSprite
	sf::Sprite expected = sf::Sprite(TIE::AssetsManager::Instance()->getTexture(TEST_TEXTURE));
	expected.setPosition(sf::Vector2f(132, 256));
	expected.setOrigin(sf::Vector2f(10, 10));
	expected.setScale(sf::Vector2f(3, 3));

	TIE::TIEntity entity = TIE::TIEntity();
	entity.setSprite(expected);
	const sf::Sprite actual = entity.getSprite();

	ASSERT_EQ(expected.getTexture(), actual.getTexture());
	ASSERT_EQ(expected.getScale(), actual.getScale());
	ASSERT_EQ(expected.getOrigin(), actual.getOrigin());
	ASSERT_EQ(expected.getPosition(), actual.getPosition());

	sf::IntRect expectedRect = expected.getTextureRect();
	sf::IntRect actualRect = actual.getTextureRect();
	ASSERT_EQ(expectedRect.left, actualRect.left);
	ASSERT_EQ(expectedRect.top, actualRect.top);
	ASSERT_EQ(expectedRect.height, actualRect.height);
	ASSERT_EQ(expectedRect.width, actualRect.width);
}


TEST(TIEntity, EqualToOperator) {
	TIE::TIEntity entity1 = TIE::TIEntity();
	TIE::TIEntity entity2 = TIE::TIEntity();

	ASSERT_EQ(entity1, entity1);
	ASSERT_EQ(entity2, entity2);
}


TEST(TIEntity, NotEqualToOperator) {
	TIE::TIEntity entity1 = TIE::TIEntity();
	TIE::TIEntity entity2 = TIE::TIEntity();

	ASSERT_NE(entity1, entity2);
}


TEST(TIEntity, AssignmentOperator) {
	TIE::TIEntity entity1 = TIE::TIEntity();
	TIE::TIEntity entity2 = TIE::TIEntity();

	entity1 = entity2;
	ASSERT_NE(entity1, entity2);
}


//TEST(TIEntity, RecieveMessage) {}


//TEST(TIEntity, UpdateState) {}