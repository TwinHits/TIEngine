#include "componentsystems/SpriteComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/ShapeComponentSystem.h"
#include "objects/components/SpriteComponent.h"
#include "objects/components/ShapeComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/AssetsManager.h"
#include "utils/ComponentSystems.h"
#include "utils/StringHelpers.h"

using namespace TIE;

void SpriteComponentSystem::update(const float delta) {
	for (auto& c : this->components) {
		c.spriteComponent.setPosition(PositionComponentSystem::Instance()->getWorldPosition(c.tientity));
		if (c.spriteComponent.isRotates()) {
			c.spriteComponent.setRotation(PositionComponentSystem::Instance()->getWorldRotation(c.tientity));
		}
	}
}


void SpriteComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
    SpriteComponent& spriteComponent = tientity.addComponent<SpriteComponent>();
    PositionComponent& positionComponent = tientity.addComponent<PositionComponent>();
    Components components = { spriteComponent, positionComponent, tientity };
    this->components.push_back(components);

    spriteComponent.setPosition(positionComponent.position);

	std::string& textureName = ComponentSystems::getFactoryValue<std::string>(factory, SpriteComponentSystem::TEXTURE, "missing_texture.png", tientity);
    sf::Texture& texture = AssetsManager::Instance()->getTexture(textureName);
    spriteComponent.setTexture(texture, true);
	
	float width = ComponentSystems::getFactoryValue<float>(factory, SpriteComponentSystem::WIDTH, texture.getSize().x, tientity);
	float height = ComponentSystems::getFactoryValue<float>(factory, SpriteComponentSystem::HEIGHT, texture.getSize().y, tientity);
	if (width != texture.getSize().x && height == texture.getSize().y) {
		height = texture.getSize().y * (width / texture.getSize().x);
	}
	if (height != texture.getSize().y && width == texture.getSize().x) {
		width = texture.getSize().x * (height / texture.getSize().y);
	}

	bool repeated = ComponentSystems::getFactoryValue<bool>(factory, SpriteComponentSystem::REPEATED, false, tientity);
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
	float originXOffset = ComponentSystems::getFactoryValue<float>(factory, SpriteComponentSystem::ORIGIN_X_OFFSET, 0, tientity);
	float originYOffset = ComponentSystems::getFactoryValue<float>(factory, SpriteComponentSystem::ORIGIN_Y_OFFSET, 0, tientity);
    spriteComponent.setOrigin((spriteSize.width / 2) - (originXOffset / spriteComponent.getScale().x), (spriteSize.height / 2) - (originYOffset / spriteComponent.getScale().y));
	
	bool drawn = ComponentSystems::getFactoryValue<bool>(factory, SpriteComponentSystem::DRAWN, true, tientity);
    spriteComponent.setDrawn(drawn);

	bool rotates = ComponentSystems::getFactoryValue<bool>(factory, SpriteComponentSystem::ROTATES, true, tientity);
	spriteComponent.setRotates(rotates);

	bool showWireframe = ComponentSystems::getFactoryValue<bool>(factory, SpriteComponentSystem::SHOW_WIREFRAME, false, tientity);
	if (showWireframe) {
		ShapeComponentSystem::Instance()->addWireframe(tientity);
	}
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
