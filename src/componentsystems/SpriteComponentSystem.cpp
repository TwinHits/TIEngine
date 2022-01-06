#include "componentsystems/SpriteComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/SpriteComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/AssetsManager.h"
#include "utils/ComponentSystems.h"
#include "utils/StringHelpers.h"

using namespace TIE;

void SpriteComponentSystem::update(const float delta) {
	for (auto& c : this->components) {
		c.spriteComponent.setPosition(c.positionComponent.position);
	}
}


void SpriteComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
    SpriteComponent& spriteComponent = tientity.addComponent<SpriteComponent>();
    PositionComponent& positionComponent = tientity.addComponent<PositionComponent>();
    Components components = { spriteComponent, positionComponent };
    this->components.push_back(components);

	std::string& textureName = ComponentSystems::getFactoryValue<std::string>(factory, SpriteComponentSystem::TEXTURE, "missing_texture.png", tientity);
    sf::Texture& texture = AssetsManager::Instance()->getTexture(textureName);
    spriteComponent.setTexture(texture, true);

	bool repeated = ComponentSystems::getFactoryValue<bool>(factory, SpriteComponentSystem::REPEATED, false, tientity);
	float width = ComponentSystems::getFactoryValue<float>(factory, SpriteComponentSystem::WIDTH, texture.getSize().x, tientity);
	float height = ComponentSystems::getFactoryValue<float>(factory, SpriteComponentSystem::HEIGHT, texture.getSize().y, tientity);

	if (repeated) {
		texture.setRepeated(repeated);
		spriteComponent.setTextureRect(sf::IntRect(0, 0, width, height));
	} else {
		// Only scale texture to the provided size if the texture is not repeated
		float xScale = width / texture.getSize().x;
		float yScale = height / texture.getSize().y;
		spriteComponent.scale(sf::Vector2f(xScale, yScale));
	}

    sf::FloatRect spriteSize = spriteComponent.getLocalBounds();
    spriteComponent.setOrigin(spriteSize.width / 2, spriteSize.height / 2);
    spriteComponent.setPosition(positionComponent.position);
    spriteComponent.setDrawn(true);
}


bool SpriteComponentSystem::removeComponent(TIEntity& tientity) {
	SpriteComponent* spriteComponent = tientity.getComponent<SpriteComponent>();
	if (spriteComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->spriteComponent == spriteComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<SpriteComponent>();
	} else {
		return false;
	}
}


const std::string& SpriteComponentSystem::getName() {
	return SpriteComponentSystem::SPRITE;
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
