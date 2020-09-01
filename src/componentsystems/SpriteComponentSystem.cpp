#include "componentsystems/SpriteComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/SpriteComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/AssetsManager.h"
#include "utils/StringHelpers.h"

using namespace TIE;

const std::string SpriteComponentSystem::DRAWN = "drawn";
const std::string SpriteComponentSystem::TEXTURE = "texture";
const std::string SpriteComponentSystem::WIDTH = "width";
const std::string SpriteComponentSystem::HEIGHT = "height";
const std::string SpriteComponentSystem::REPEATED = "repeated";
const std::string SpriteComponentSystem::POSITION_X = "drawn.position.x";
const std::string SpriteComponentSystem::POSITION_Y = "drawn.position.y";
const std::string SpriteComponentSystem::ROTATION = "drawn.rotation";
const std::string SpriteComponentSystem::TEXTURE_KEY = SpriteComponentSystem::DRAWN + '.' + SpriteComponentSystem::TEXTURE;
const std::string SpriteComponentSystem::DRAWN_KEY = SpriteComponentSystem::DRAWN + '.' + SpriteComponentSystem::DRAWN;

void SpriteComponentSystem::update(const float delta) {
	for (auto& c : this->components) {
		c.spriteComponent.setPosition(c.positionComponent.getPosition());
	}
}


SpriteComponent& SpriteComponentSystem::addComponent(TIEntity& entity) {
	return entity.addComponent<SpriteComponent>();
}


void SpriteComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& entity) {

	if (factory.stringValues.count(SpriteComponentSystem::TEXTURE_KEY)) {
        SpriteComponent& spriteComponent = entity.addComponent<SpriteComponent>();
        PositionComponent& positionComponent = entity.addComponent<PositionComponent>();
        Components components = { spriteComponent, positionComponent };
		this->components.push_back(components);

		std::string textureName = factory.stringValues.at(SpriteComponentSystem::TEXTURE_KEY);
		sf::Texture& texture = AssetsManager::Instance()->getTexture(textureName);

		sf::Vector2f position = sf::Vector2f(0, 0);
		float angle = 0;
		if (factory.floatValues.count(SpriteComponentSystem::POSITION_X)) {
			position.x = factory.floatValues.at(SpriteComponentSystem::POSITION_X);
		}

		if (factory.floatValues.count(SpriteComponentSystem::POSITION_Y)) {
			position.y = factory.floatValues.at(SpriteComponentSystem::POSITION_Y);
		}
		
		if (factory.floatValues.count(SpriteComponentSystem::ROTATION)) {
			angle = factory.floatValues.at(SpriteComponentSystem::ROTATION);
		}
		positionComponent.setPosition(position);
		positionComponent.setAngle(angle);

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
