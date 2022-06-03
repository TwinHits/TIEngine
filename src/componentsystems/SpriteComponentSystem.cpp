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
		c.spriteComponent.setPosition(c.positionComponent.worldPosition);
		c.spriteComponent.setRotation(c.positionComponent.worldRotation);
	}
}


void SpriteComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
    SpriteComponent& spriteComponent = tientity.addComponent<SpriteComponent>();
	PositionComponent& positionComponent = tientity.addComponent<PositionComponent>();
    Components components = { spriteComponent, positionComponent };
    this->components.push_back(components);

    spriteComponent.setPosition(positionComponent.position);

	std::string& textureName = ComponentSystems::getFactoryValue<std::string>(factory, SpriteComponentSystem::TEXTURE, SpriteComponentSystem::MISSING_TEXTURE_NAME, tientity);
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

	bool repeated = ComponentSystems::getFactoryValue<bool>(factory, SpriteComponentSystem::REPEATED, texture.isRepeated(), tientity);
	if (repeated) {
		texture.setRepeated(repeated);
		spriteComponent.setTextureRect(sf::IntRect(0, 0, width, height));
	} else {
		// Only scale texture to the provided size if the texture is not repeated
		float xScale = width / texture.getSize().x;
		float yScale = height / texture.getSize().y;
		spriteComponent.scale(sf::Vector2f(xScale, yScale));
	}

	spriteComponent.setOrigin(spriteComponent.getLocalBounds().width / 2, spriteComponent.getLocalBounds().height / 2);

	bool drawn = ComponentSystems::getFactoryValue<bool>(factory, SpriteComponentSystem::DRAWN, spriteComponent.isDrawn(), tientity);
    spriteComponent.setDrawn(drawn);

	bool rotates = ComponentSystems::getFactoryValue<bool>(factory, SpriteComponentSystem::ROTATES, spriteComponent.isRotates(), tientity);
	spriteComponent.setRotates(rotates);

	bool showWireframe = ComponentSystems::getFactoryValue<bool>(factory, SpriteComponentSystem::SHOW_WIREFRAME, SpriteComponentSystem::SHOW_WIREFRAME_DEFAULT, tientity);
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


bool SpriteComponentSystem::setComponentProperty(const std::string& key, bool value, TIEntity& tientity) {
    return false;
}


bool SpriteComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity)  {
    return false;
}


bool SpriteComponentSystem::setComponentProperty(const std::string& key, const std::string& value, TIEntity& tientity)  {
    return false;
}


sol::object SpriteComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
	return ScriptManager::Instance()->getObjectFromValue(nullptr);
}
