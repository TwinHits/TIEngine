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
#include "utils/TIEMath.h"

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

	bool repeated = ComponentSystems::getFactoryValue<bool>(factory, SpriteComponentSystem::REPEATED, texture.isRepeated(), tientity);
    texture.setRepeated(repeated);
	
	float width = ComponentSystems::getFactoryValue<float>(factory, SpriteComponentSystem::WIDTH, texture.getSize().x, tientity);
	float height = ComponentSystems::getFactoryValue<float>(factory, SpriteComponentSystem::HEIGHT, texture.getSize().y, tientity);
	this->calcluateTextureFields(spriteComponent, width, height);

	bool drawn = ComponentSystems::getFactoryValue<bool>(factory, SpriteComponentSystem::DRAWN, spriteComponent.isDrawn(), tientity);
    spriteComponent.setDrawn(drawn);

	bool rotates = ComponentSystems::getFactoryValue<bool>(factory, SpriteComponentSystem::ROTATES, spriteComponent.isRotates(), tientity);
	spriteComponent.setRotates(rotates);

	bool showWireframe = ComponentSystems::getFactoryValue<bool>(factory, SpriteComponentSystem::SHOW_WIREFRAME, SpriteComponentSystem::SHOW_WIREFRAME_DEFAULT, tientity);
	if (showWireframe) {
		ShapeComponentSystem::Instance()->addWireframe(tientity, spriteComponent);
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
	SpriteComponent* component = tientity.getComponent<SpriteComponent>();
	if (component != nullptr) {
		if (key == SpriteComponentSystem::WIDTH) {
			this->calcluateTextureFields(*component, value, component->getScaledSize().y);
		} else if (key == SpriteComponentSystem::HEIGHT) {
			this->calcluateTextureFields(*component, component->getScaledSize().x, value);
		}
	}
	return false;
}


bool SpriteComponentSystem::setComponentProperty(const std::string& key, const std::string& value, TIEntity& tientity)  {
	SpriteComponent* component = tientity.getComponent<SpriteComponent>();
	if (component != nullptr) {
		if (key == SpriteComponentSystem::TEXTURE) {
			sf::Texture& texture = AssetsManager::Instance()->getTexture(value);
			component->setTexture(texture, true);
		}
	}
	return false;
}


sol::object SpriteComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
	return ScriptManager::Instance()->getObjectFromValue(nullptr);
}


ComponentSystems::ComponentSystemPropertiesMap& SpriteComponentSystem::populateComponentSystemsPropertiesMap(ComponentSystems::ComponentSystemPropertiesMap& map) {
	ComponentSystems::insertComponentPropertyIntoMap(SpriteComponentSystem::DRAWN, map);
	ComponentSystems::insertComponentPropertyIntoMap(SpriteComponentSystem::TEXTURE, map);
	ComponentSystems::insertComponentPropertyIntoMap(SpriteComponentSystem::WIDTH, map);
	ComponentSystems::insertComponentPropertyIntoMap(SpriteComponentSystem::HEIGHT, map);
	ComponentSystems::insertComponentPropertyIntoMap(SpriteComponentSystem::ORIGIN_X_OFFSET, map);
	ComponentSystems::insertComponentPropertyIntoMap(SpriteComponentSystem::ORIGIN_Y_OFFSET, map);
	ComponentSystems::insertComponentPropertyIntoMap(SpriteComponentSystem::REPEATED, map);
	ComponentSystems::insertComponentPropertyIntoMap(SpriteComponentSystem::ROTATES, map);
	ComponentSystems::insertComponentPropertyIntoMap(SpriteComponentSystem::SHOW_WIREFRAME, map);
	return map;
}


void SpriteComponentSystem::calcluateTextureFields(SpriteComponent& spriteComponent, float width, float height) {

	const sf::Texture* texture = spriteComponent.getTexture();
	if (texture != nullptr) {
		const sf::Vector2f& scaledSize = spriteComponent.getScaledSize();

		if (!Math::areFloatsEqual(width, scaledSize.x) && Math::areFloatsEqual(height, scaledSize.y)) {
			height = scaledSize.y * (width / scaledSize.x);
		}

		if (!Math::areFloatsEqual(height, scaledSize.y) && Math::areFloatsEqual(width, scaledSize.x)) {
			width = scaledSize.x * (height / scaledSize.y);
		}

		if (texture->isRepeated()) {
			spriteComponent.setTextureRect(sf::IntRect(0, 0, width, height));
		} else {
			// Only scale texture to the provided size if the texture is not repeated
			float xScale = width / scaledSize.x;
			float yScale = height / scaledSize.y;
			spriteComponent.scale(sf::Vector2f(xScale, yScale));
		}

		spriteComponent.setOrigin(spriteComponent.getLocalBounds().width / 2, spriteComponent.getLocalBounds().height / 2);
	}

}
