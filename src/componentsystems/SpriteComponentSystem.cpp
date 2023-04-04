#include "componentsystems/SpriteComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/ShapeComponentSystem.h"
#include "objects/components/SpriteComponent.h"
#include "objects/components/ShapeComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/tientities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/AssetsManager.h"
#include "utils/ComponentSystems.h"
#include "utils/StringHelpers.h"
#include "utils/TIEMath.h"

using namespace TIE;

SpriteComponentSystem::SpriteComponentSystem() {
	this->setName(SpriteComponentSystem::SPRITE);
	ComponentSystems::insertComponentPropertyIntoMap(SpriteComponentSystem::DRAWN, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(SpriteComponentSystem::TEXTURE, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(SpriteComponentSystem::WIDTH, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(SpriteComponentSystem::HEIGHT, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(SpriteComponentSystem::ORIGIN_X, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(SpriteComponentSystem::ORIGIN_Y, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(SpriteComponentSystem::REPEATED, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(SpriteComponentSystem::ROTATES, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(SpriteComponentSystem::SHOW_WIREFRAME, this->componentPropertyMap);
	ComponentSystems::insertComponentPropertyIntoMap(SpriteComponentSystem::CONSTRAIN_PROPORTIONS, this->componentPropertyMap);
}


void SpriteComponentSystem::update(const float delta) {
	for (auto& c : this->components) {
		c.spriteComponent.setPosition(c.positionComponent.worldPosition);
		if (c.spriteComponent.isRotates()) {
			c.spriteComponent.setRotation(c.positionComponent.worldRotation);
		}
	}
}


SpriteComponent& SpriteComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<SpriteComponent>()) {
		SpriteComponent& spriteComponent = tientity.addComponent<SpriteComponent>();
		PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);
		this->components.push_back({ spriteComponent, positionComponent });
		return spriteComponent;
	} else {
		return *tientity.getComponent<SpriteComponent>();
	}
}


SpriteComponent& SpriteComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
	SpriteComponent& spriteComponent = this->addComponent(tientity);
	PositionComponent& positionComponent = PositionComponentSystem::Instance()->addComponent(tientity);

    spriteComponent.setPosition(positionComponent.position);

	std::string& textureName = ComponentSystems::getFactoryValue<std::string>(factory, SpriteComponentSystem::TEXTURE, SpriteComponentSystem::MISSING_TEXTURE_NAME, tientity);
    sf::Texture& texture = AssetsManager::Instance()->getTexture(textureName);

	bool repeated = ComponentSystems::getFactoryValue<bool>(factory, SpriteComponentSystem::REPEATED, texture.isRepeated(), tientity);
    texture.setRepeated(repeated);

	bool constrainProportions = ComponentSystems::getFactoryValue<bool>(factory, SpriteComponentSystem::CONSTRAIN_PROPORTIONS, spriteComponent.isConstrainProportions(), tientity);
	spriteComponent.setConstrainProportions(constrainProportions);

	float width = ComponentSystems::getFactoryValue<float>(factory, SpriteComponentSystem::WIDTH, texture.getSize().x, tientity);
	float height = ComponentSystems::getFactoryValue<float>(factory, SpriteComponentSystem::HEIGHT, texture.getSize().y, tientity);
	this->setTextureFields(spriteComponent, texture, width, height);

	float originX = ComponentSystems::getFactoryValue<float>(factory, SpriteComponentSystem::ORIGIN_X, spriteComponent.getLocalBounds().width / 2, tientity);
	float originY = ComponentSystems::getFactoryValue<float>(factory, SpriteComponentSystem::ORIGIN_Y, spriteComponent.getLocalBounds().height / 2, tientity);
	spriteComponent.setOrigin(originX, originY);

	bool drawn = ComponentSystems::getFactoryValue<bool>(factory, SpriteComponentSystem::DRAWN, spriteComponent.isDrawn(), tientity);
    spriteComponent.setDrawn(drawn);

	bool rotates = ComponentSystems::getFactoryValue<bool>(factory, SpriteComponentSystem::ROTATES, spriteComponent.isRotates(), tientity);
	spriteComponent.setRotates(rotates);

	bool showWireframe = ComponentSystems::getFactoryValue<bool>(factory, SpriteComponentSystem::SHOW_WIREFRAME, SpriteComponentSystem::SHOW_WIREFRAME_DEFAULT, tientity);
	if (showWireframe) {
		ShapeComponentSystem::Instance()->addWireframe(tientity, spriteComponent);
	}

	return spriteComponent;
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


void SpriteComponentSystem::setComponentProperty(const std::string& key, bool value, TIEntity& tientity) {
	SpriteComponent& component = this->addComponent(tientity);
    if (key == SpriteComponentSystem::CONSTRAIN_PROPORTIONS) {
        component.setConstrainProportions(value);
    } else if (key == SpriteComponentSystem::DRAWN) {
        component.setDrawn(value);
    }
}


void SpriteComponentSystem::setComponentProperty(const std::string& key, float value, TIEntity& tientity)  {
	SpriteComponent& component = this->addComponent(tientity);
    if (key == SpriteComponentSystem::WIDTH) {
        this->setTextureFields(component, value, component.getLocalBounds().height);
    } else if (key == SpriteComponentSystem::HEIGHT) {
        this->setTextureFields(component, component.getLocalBounds().width, value);
    }
}


void SpriteComponentSystem::setComponentProperty(const std::string& key, const std::string& value, TIEntity& tientity)  {
	SpriteComponent& component = this->addComponent(tientity);
    if (key == SpriteComponentSystem::TEXTURE) {
        const sf::Texture& texture = AssetsManager::Instance()->getTexture(value);
        this->setTextureFields(component, texture);
    }
}


sol::object SpriteComponentSystem::getComponentProperty(const std::string& key, TIEntity& tientity) {
	SpriteComponent* component = tientity.getComponent<SpriteComponent>();
	if (component != nullptr) {
		if (key == SpriteComponentSystem::CONSTRAIN_PROPORTIONS) {
			return ScriptManager::Instance()->getObjectFromValue(component->isConstrainProportions());
		} else if (key == SpriteComponentSystem::WIDTH) {
			return ScriptManager::Instance()->getObjectFromValue(component->getGlobalBounds().width);
		} else if (key == SpriteComponentSystem::HEIGHT) {
			return ScriptManager::Instance()->getObjectFromValue(component->getGlobalBounds().width);
		}
	}
	return ScriptManager::Instance()->getObjectFromValue(nullptr);
}


void SpriteComponentSystem::setTextureFields(SpriteComponent& spriteComponent, const sf::Texture& texture) {
	return this->setTextureFields(spriteComponent, texture, spriteComponent.getLocalBounds().width, spriteComponent.getLocalBounds().height);
}


void SpriteComponentSystem::setTextureFields(SpriteComponent& spriteComponent, float width, float height) {
	return this->setTextureFields(spriteComponent, *spriteComponent.getTexture(), width, height);
}


void SpriteComponentSystem::setTextureFields(SpriteComponent& spriteComponent, const sf::Texture& texture, float width, float height) {

    bool isCenterOrigin = spriteComponent.isCenterOrigin();
	spriteComponent.setTexture(texture, true);

	if (spriteComponent.isConstrainProportions()) {
		const sf::FloatRect& localBounds = spriteComponent.getLocalBounds();
		if (!Math::areFloatsEqual(width, localBounds.width) && Math::areFloatsEqual(height, localBounds.height)) {
			height = localBounds.height * (width / localBounds.width);
		}

		if (!Math::areFloatsEqual(height, localBounds.height) && Math::areFloatsEqual(width, localBounds.width)) {
			width = localBounds.width * (height / localBounds.height);
		}
	}
	
    if (texture.isRepeated()) {
        spriteComponent.setTextureRect(sf::IntRect(0, 0, width, height));
    } else {
        // Only scale texture to the provided size if the texture is not repeated
        float xScale = width / spriteComponent.getLocalBounds().width;
        float yScale = height / spriteComponent.getLocalBounds().height;
        spriteComponent.setScale(sf::Vector2f(xScale, yScale));
    }

	if (isCenterOrigin) {
		spriteComponent.setOrigin(spriteComponent.getLocalBounds().width / 2, spriteComponent.getLocalBounds().height / 2);
	}

}
