#include "componentsystems/SpriteComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/AssetsManager.h"
#include "utilities/StringHelpers.h"

using namespace TIE;

const std::string SpriteComponentSystem::DRAWN = "drawn";
const std::string SpriteComponentSystem::TEXTURE = "texture";
const std::string SpriteComponentSystem::ROTATION = "rotation";
const std::string SpriteComponentSystem::TEXTURE_KEY = SpriteComponentSystem::DRAWN + '.' + SpriteComponentSystem::TEXTURE;
const std::string SpriteComponentSystem::DRAWN_KEY = SpriteComponentSystem::DRAWN + '.' + SpriteComponentSystem::DRAWN;
const std::string SpriteComponentSystem::ROTATION_KEY = SpriteComponentSystem::DRAWN + '.' + SpriteComponentSystem::ROTATION;

void SpriteComponentSystem::update(TIEntity& tientity, const float delta) {

}


SpriteComponent& SpriteComponentSystem::addComponent(TIEntity& entity) {
	return entity.addComponent<SpriteComponent>();
}


void SpriteComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& entity) {

	SpriteComponent* spritePtr = nullptr;
	if (factory.stringValues.count(SpriteComponentSystem::TEXTURE_KEY)) {
		std::string textureName = factory.stringValues.at(SpriteComponentSystem::TEXTURE_KEY);
		const sf::Texture& texture = AssetsManager::Instance()->getTexture(textureName);
		SpriteComponent& spriteComponent = entity.addComponent<SpriteComponent>();
        sf::FloatRect size = spriteComponent.getLocalBounds();
        spriteComponent.setOrigin(size.width / 2, size.height / 2);
		spriteComponent.setTexture(texture, true);

		if (factory.floatValues.count(SpriteComponentSystem::ROTATION_KEY)) {
			float rotation = factory.floatValues.at(SpriteComponentSystem::ROTATION_KEY);
			spriteComponent.setRotation(rotation);
		}

		if (factory.boolValues.count(SpriteComponentSystem::DRAWN_KEY)) {
			bool drawn = factory.boolValues.at(SpriteComponentSystem::DRAWN_KEY);
			spriteComponent.setDrawn(drawn);
		}
	}
}


/*
sf::Transform GraphicsComponentSystem::getWorldTransform() const {
	sf::Transform transform = sf::Transform::Identity;

	for (const TIEntity* n = this; n != nullptr; n = n->parent) {
		transform = n->getTransform() * transform;
	}

	return transform;
}


sf::Vector2f GraphicsComponentSystem::getWorldPosition() const {
	return this->getWorldTransform() * sf::Vector2f();
}

float GraphicsComponentSystem::getWorldRotation() const {
	float rotation = 0;

	for (SceneNode* n = parent; n != nullptr; n = n->parent) {
		rotation += n->getRotation();
	}

	rotation += this->getRotation();

	return rotation;
}
*/
