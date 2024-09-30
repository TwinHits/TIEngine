#include "componentsystems/SpriteComponentSystem.h" 

#include "componentsystems/PositionComponentSystem.h"
#include "componentsystems/WireframeComponentSystem.h"
#include "managers/AssetsManager.h"
#include "managers/ComponentSystemsManager.h"
#include "managers/ScriptManager.h"
#include "utils/TIEMath.h"

using namespace TIE;

SpriteComponentSystem::SpriteComponentSystem() {
	this->setName(SpriteComponentSystem::SPRITE);

	ComponentSystemsManager::Instance()->registerComponentPropertyKey(SpriteComponentSystem::DRAWN, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(SpriteComponentSystem::TEXTURE, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(SpriteComponentSystem::WIDTH, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(SpriteComponentSystem::HEIGHT, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(SpriteComponentSystem::ORIGIN_X, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(SpriteComponentSystem::ORIGIN_Y, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(SpriteComponentSystem::REPEATED, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(SpriteComponentSystem::ROTATES, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(SpriteComponentSystem::CONSTRAIN_PROPORTIONS, this);
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
	const ScriptTableReader& reader = factory.getReader().getReader(SpriteComponentSystem::SPRITE);

    spriteComponent.setPosition(positionComponent.position);

	const std::string& textureName = reader.get<std::string>(SpriteComponentSystem::TEXTURE, SpriteComponentSystem::MISSING_TEXTURE_NAME);
    sf::Texture& texture = AssetsManager::Instance()->getTexture(textureName);

	const bool& repeated = reader.get<bool>(SpriteComponentSystem::REPEATED, texture.isRepeated());
    texture.setRepeated(repeated);

	const bool& constrainProportions = reader.get<bool>(SpriteComponentSystem::CONSTRAIN_PROPORTIONS, spriteComponent.isConstrainProportions());
	spriteComponent.setConstrainProportions(constrainProportions);

	const float& width = reader.get<float>(SpriteComponentSystem::WIDTH, texture.getSize().x);
	const float& height = reader.get<float>(SpriteComponentSystem::HEIGHT, texture.getSize().y);
	this->setTextureFields(spriteComponent, texture, width, height);


	const ScriptTableReader& originReader = reader.getReader(SpriteComponentSystem::ORIGIN);
    const float& originX = originReader.get<float>(SpriteComponentSystem::ORIGIN_X, spriteComponent.getLocalBounds().width / 2);
    const float& originY = originReader.get<float>(SpriteComponentSystem::ORIGIN_Y, spriteComponent.getLocalBounds().height / 2);
    spriteComponent.setOrigin(originX, originY);

	const bool& drawn = reader.get<bool>(SpriteComponentSystem::DRAWN, spriteComponent.isDrawn());
    spriteComponent.setDrawn(drawn);

	const bool& rotates = reader.get<bool>(SpriteComponentSystem::ROTATES, spriteComponent.isRotates());
	spriteComponent.setRotates(rotates);

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


std::pair<GlobalId, GlobalId> SpriteComponentSystem::addWireframe(TIEntity& tientity) {
	SpriteComponent* spriteComponent = tientity.getComponent<SpriteComponent>();
	if (spriteComponent) {
		return WireframeComponentSystem::Instance()->createWireframe(tientity, spriteComponent->getLocalBounds(), spriteComponent->getOrigin());
	}
	return std::pair(0,0);
}


void SpriteComponentSystem::setTextureFields(SpriteComponent& spriteComponent, const sf::Texture& texture) {
	return this->setTextureFields(spriteComponent, texture, texture.getSize().x, texture.getSize().y);
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
