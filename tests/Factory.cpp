#include "pch.h"

TEST(Factory, Create) {
	TIE::Factory<TIE::TIEntity> factory = TIE::Factory<TIE::TIEntity>();
	TIE::GlobalId id = factory.create();
	const TIE::TIEntity& entity = TIE::TIEntityManager::Instance()->getTIEntity(id);
	
	//Didn't throw exception for no TIEntity with that id
	ASSERT_EQ(id, entity.getId());
}


TEST(Factory, CreateFromPointer) {
	std::unique_ptr<TIE::TIEntity> ptr = std::make_unique<TIE::TIEntity>();

	TIE::Factory<TIE::TIEntity> factory = TIE::Factory<TIE::TIEntity>();
	TIE::GlobalId id = factory.create(std::move(ptr));
	const TIE::TIEntity& entity = TIE::TIEntityManager::Instance()->getTIEntity(id);
	
	//Didn't throw exception for no TIEntity with that id
	ASSERT_EQ(id, entity.getId());
}