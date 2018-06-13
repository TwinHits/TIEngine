#include "../../pch.h"

#include "../../Constants.h"

TEST(TIEntity, GetId) {
	TIE::HashManager::Instance()->setSeed(TIE::ENTITY_UNUSED_ID);
	//plus 2 for the clock initialized inside the constructor	
	TIE::GlobalId expected = TIE::ENTITY_UNUSED_ID+2;
	TIE::TIEntity entity = TIE::TIEntity();
	TIE::GlobalId actual = entity.getId();

	ASSERT_EQ(expected, actual);
}


TEST(TIEntity, GetDrawn) {
	TIE::TIEntity entity = TIE::TIEntity();
	bool expected = TIE::DEFAULT_DRAW_BOOL;

	bool actual = entity.getDrawn();

	ASSERT_EQ(expected, actual);
}


TEST(TIEntity, SetDrawn) {
	TIE::TIEntity entity = TIE::TIEntity();
	bool expected = TIE::CUSTOM_DRAW_BOOL;

	entity.setDrawn(TIE::CUSTOM_DRAW_BOOL);
	bool actual = entity.getDrawn();

	ASSERT_EQ(expected, actual);
}


TEST(TIEntity, GetCollidable) {
	TIE::TIEntity entity = TIE::TIEntity();
	bool expected = TIE::DEFAULT_DRAW_BOOL;

	bool actual = entity.getCollidable();

	ASSERT_EQ(expected, actual);
}


TEST(TIEntity, SetCollidable) {
	TIE::TIEntity entity = TIE::TIEntity();
	bool expected = TIE::CUSTOM_DRAW_BOOL;

	entity.setCollidable(TIE::CUSTOM_DRAW_BOOL);
	bool actual = entity.getCollidable();

	ASSERT_EQ(expected, actual);
}


TEST(TIEntity, GetSpeed) {
	TIE::TIEntity entity = TIE::TIEntity();
	float expected = TIE::DEFAULT_SPEED_FLOAT;

	float actual = entity.getSpeed();

	ASSERT_FLOAT_EQ(expected, actual);
}

TEST(TIEntity, SetSpeed) {
	TIE::TIEntity entity = TIE::TIEntity();
	float expected = TIE::CUSTOM_SPEED_FLOAT;

	entity.setSpeed(TIE::CUSTOM_SPEED_FLOAT);
	float actual = entity.getSpeed();

	ASSERT_FLOAT_EQ(expected, actual);
}


TEST(TIEntity, GetSprite) {
	TIE::ConfigManager::Instance()->loadConfigFile(TIE::TEST_CONFIG_FILE);

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
	sf::Sprite expected = sf::Sprite(TIE::AssetsManager::Instance()->getTexture(TIE::TEST_TEXTURE));
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


TEST(TIEntity, GetAngle) {
	sf::Sprite sprite = sf::Sprite(TIE::AssetsManager::Instance()->getTexture(TIE::TEST_TEXTURE));
	sprite.setPosition(sf::Vector2f(132, 256));
	sprite.setOrigin(sf::Vector2f(10, 10));
	sprite.setScale(sf::Vector2f(3, 3));

	TIE::TIEntity entity = TIE::TIEntity();
	entity.setSprite(sprite);

	float expected = 0.0;
	float actual = entity.getAngle();

	ASSERT_FLOAT_EQ(expected, actual);
}


TEST(TIEntity, SetAngle) {
	sf::Sprite sprite = sf::Sprite(TIE::AssetsManager::Instance()->getTexture(TIE::TEST_TEXTURE));
	sprite.setPosition(sf::Vector2f(132, 256));
	sprite.setOrigin(sf::Vector2f(10, 10));
	sprite.setScale(sf::Vector2f(3, 3));

	TIE::TIEntity entity = TIE::TIEntity();
	entity.setSprite(sprite);

	float expected = 90.0;
	entity.setAngle(expected);
	float actual = entity.getAngle();

	ASSERT_FLOAT_EQ(expected, actual);
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


TEST(TIEntity, MoveRight) {
	TIE::TIEntity entity = TIE::TIEntity();
	sf::Vector2f startPosition = entity.getSprite().getPosition();
	sf::Vector2f preconditionPosition = sf::Vector2f(0.0, 0.0);

	ASSERT_FLOAT_EQ(startPosition.x, preconditionPosition.x);
	ASSERT_FLOAT_EQ(startPosition.y, preconditionPosition.y);

	float delta = 1.0;

	entity.setAngle(0.0);
	entity.move(delta);

	sf::Vector2f expected = sf::Vector2f(1.0, 0.0);
 	sf::Vector2f actual = entity.getSprite().getPosition();

	ASSERT_FLOAT_EQ(expected.x, actual.x);
	ASSERT_FLOAT_EQ(expected.y, actual.y);
}


TEST(TIEntity, MoveDownRight) {
	TIE::TIEntity entity = TIE::TIEntity();
	sf::Vector2f startPosition = entity.getSprite().getPosition();
	sf::Vector2f preconditionPosition = sf::Vector2f(0.0, 0.0);

	ASSERT_FLOAT_EQ(startPosition.x, preconditionPosition.x);
	ASSERT_FLOAT_EQ(startPosition.y, preconditionPosition.y);

	float delta = 1.0;

	entity.setAngle(45.0);
	entity.move(delta);

	sf::Vector2f expected = sf::Vector2f(0.7071067, 0.7071067);
	sf::Vector2f actual = entity.getSprite().getPosition();

	ASSERT_FLOAT_EQ(expected.x, actual.x);
	ASSERT_FLOAT_EQ(expected.y, actual.y);
}


TEST(TIEntity, MoveDown) {
	TIE::TIEntity entity = TIE::TIEntity();
	sf::Vector2f startPosition = entity.getSprite().getPosition();
	sf::Vector2f preconditionPosition = sf::Vector2f(0.0, 0.0);

	ASSERT_FLOAT_EQ(startPosition.x, preconditionPosition.x);
	ASSERT_FLOAT_EQ(startPosition.y, preconditionPosition.y);

	float delta = 1.0;

	entity.setAngle(90.0);
	entity.move(delta);

	sf::Vector2f expected = sf::Vector2f(0.0, 1.0);
 	sf::Vector2f actual = entity.getSprite().getPosition();

	ASSERT_FLOAT_EQ(expected.x, actual.x);
	ASSERT_FLOAT_EQ(expected.y, actual.y);
}


TEST(TIEntity, MoveDownLeft) {
	TIE::TIEntity entity = TIE::TIEntity();
	sf::Vector2f startPosition = entity.getSprite().getPosition();
	sf::Vector2f preconditionPosition = sf::Vector2f(0.0, 0.0);

	ASSERT_FLOAT_EQ(startPosition.x, preconditionPosition.x);
	ASSERT_FLOAT_EQ(startPosition.y, preconditionPosition.y);

	float delta = 1.0;

	entity.setAngle(135.0);
	entity.move(delta);

	sf::Vector2f expected = sf::Vector2f(-0.7071067, 0.7071067);
 	sf::Vector2f actual = entity.getSprite().getPosition();

	ASSERT_FLOAT_EQ(expected.x, actual.x);
	ASSERT_FLOAT_EQ(expected.y, actual.y);
}


TEST(TIEntity, MoveLeft) {
	TIE::TIEntity entity = TIE::TIEntity();
	sf::Vector2f startPosition = entity.getSprite().getPosition();
	sf::Vector2f preconditionPosition = sf::Vector2f(0.0, 0.0);

	ASSERT_FLOAT_EQ(startPosition.x, preconditionPosition.x);
	ASSERT_FLOAT_EQ(startPosition.y, preconditionPosition.y);

	float delta = 1.0;

	entity.setAngle(180.0);
	entity.move(delta);

	sf::Vector2f expected = sf::Vector2f(-1.0, 0.0);
 	sf::Vector2f actual = entity.getSprite().getPosition();

	ASSERT_FLOAT_EQ(expected.x, actual.x);
	ASSERT_FLOAT_EQ(expected.y, actual.y);
}

TEST(TIEntity, MoveUpLeft) {
	TIE::TIEntity entity = TIE::TIEntity();
	sf::Vector2f startPosition = entity.getSprite().getPosition();
	sf::Vector2f preconditionPosition = sf::Vector2f(0.0, 0.0);

	ASSERT_FLOAT_EQ(startPosition.x, preconditionPosition.x);
	ASSERT_FLOAT_EQ(startPosition.y, preconditionPosition.y);

	float delta = 1.0;

	entity.setAngle(225.0);
	entity.move(delta);

	sf::Vector2f expected = sf::Vector2f(-0.7071067, -0.7071067);
 	sf::Vector2f actual = entity.getSprite().getPosition();

	ASSERT_FLOAT_EQ(expected.x, actual.x);
	ASSERT_FLOAT_EQ(expected.y, actual.y);
}


TEST(TIEntity, MoveUp) {
	TIE::TIEntity entity = TIE::TIEntity();
	sf::Vector2f startPosition = entity.getSprite().getPosition();
	sf::Vector2f preconditionPosition = sf::Vector2f(0.0, 0.0);

	ASSERT_FLOAT_EQ(startPosition.x, preconditionPosition.x);
	ASSERT_FLOAT_EQ(startPosition.y, preconditionPosition.y);

	float delta = 1.0;
	entity.setAngle(270.0);
	entity.move(delta);

	sf::Vector2f expected = sf::Vector2f(0.0, -1.0);
	sf::Vector2f actual = entity.getSprite().getPosition();

	ASSERT_FLOAT_EQ(expected.x, actual.x);
	ASSERT_FLOAT_EQ(expected.y, actual.y);
}


TEST(TIEntity, MoveUpRight) {
	TIE::TIEntity entity = TIE::TIEntity();
	sf::Vector2f startPosition = entity.getSprite().getPosition();
	sf::Vector2f preconditionPosition = sf::Vector2f(0.0, 0.0);

	ASSERT_FLOAT_EQ(startPosition.x, preconditionPosition.x);
	ASSERT_FLOAT_EQ(startPosition.y, preconditionPosition.y);

	float delta = 1.0;
	entity.setAngle(315.0);
	entity.move(delta);

	sf::Vector2f expected = sf::Vector2f(0.7071067, -0.7071067);
	sf::Vector2f actual = entity.getSprite().getPosition();

	ASSERT_FLOAT_EQ(expected.x, actual.x);
	ASSERT_FLOAT_EQ(expected.y, actual.y);
}


//TEST(TIEntity, RecieveMessage) {}


//TEST(TIEntity, UpdateState) {}
