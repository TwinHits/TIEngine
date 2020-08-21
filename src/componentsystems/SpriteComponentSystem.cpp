#include "componentsystems/SpriteComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/SpriteComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/AssetsManager.h"
#include "utils/StringHelpers.h"

using namespace TIE;

const std::string SpriteComponentSystem::DRAWN = "drawn";
const std::string SpriteComponentSystem::TEXTURE = "texture";
const std::string SpriteComponentSystem::ROTATION = "rotation";
const std::string SpriteComponentSystem::WIDTH = "width";
const std::string SpriteComponentSystem::HEIGHT = "height";
const std::string SpriteComponentSystem::REPEATED = "repeated";
const std::string SpriteComponentSystem::TEXTURE_KEY = SpriteComponentSystem::DRAWN + '.' + SpriteComponentSystem::TEXTURE;
const std::string SpriteComponentSystem::DRAWN_KEY = SpriteComponentSystem::DRAWN + '.' + SpriteComponentSystem::DRAWN;
const std::string SpriteComponentSystem::ROTATION_KEY = SpriteComponentSystem::DRAWN + '.' + SpriteComponentSystem::ROTATION;

void SpriteComponentSystem::update(const float delta) {

}


SpriteComponent& SpriteComponentSystem::addComponent(TIEntity& entity) {
	return entity.addComponent<SpriteComponent>();
}


void SpriteComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& entity) {

	SpriteComponent& spriteComponent = entity.addComponent<SpriteComponent>();
	if (factory.stringValues.count(SpriteComponentSystem::TEXTURE_KEY)) {
		std::string textureName = factory.stringValues.at(SpriteComponentSystem::TEXTURE_KEY);
		sf::Texture& texture = AssetsManager::Instance()->getTexture(textureName);

		if (factory.floatValues.count(SpriteComponentSystem::ROTATION_KEY)) {
			float rotation = factory.floatValues.at(SpriteComponentSystem::ROTATION_KEY);
			spriteComponent.setRotation(rotation);
		}

		if (factory.boolValues.count(SpriteComponentSystem::DRAWN_KEY)) {
			bool drawn = factory.boolValues.at(SpriteComponentSystem::DRAWN_KEY);
			spriteComponent.setDrawn(drawn);
		}

		if (factory.boolValues.count(SpriteComponentSystem::DRAWN + "." + SpriteComponentSystem::REPEATED)) {
			bool repeated = factory.boolValues.at(SpriteComponentSystem::DRAWN + "." + SpriteComponentSystem::REPEATED);
			if (repeated) {
				texture.setRepeated(repeated);
				float width = texture.getSize().x;
				float height = texture.getSize().y;

				if (factory.floatValues.count(SpriteComponentSystem::DRAWN + "." + SpriteComponentSystem::WIDTH)) {
					width = factory.floatValues.at(SpriteComponentSystem::DRAWN + "." + SpriteComponentSystem::WIDTH);
				}

				if (factory.floatValues.count(SpriteComponentSystem::DRAWN + "." + SpriteComponentSystem::HEIGHT)) {
					height = factory.floatValues.at(SpriteComponentSystem::DRAWN + "." + SpriteComponentSystem::HEIGHT);
				}

				spriteComponent.setTextureRect(sf::IntRect(0, 0, width, height));
			}
		}

		spriteComponent.setTexture(texture, false);
        sf::FloatRect size = spriteComponent.getLocalBounds();
        spriteComponent.setOrigin(size.width / 2, size.height / 2);
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
