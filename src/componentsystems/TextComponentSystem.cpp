#include "componentsystems/TextComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/TextComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/AssetsManager.h"
#include "utils/StringHelpers.h"

using namespace TIE;

void TextComponentSystem::update(const float delta) {
	for (auto& c : this->components) {	
		c.textComponent.setPosition(c.positionComponent.position + c.textComponent.getOffset());
	}
}


void TextComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& entity) {

	if (factory.stringValues.count(TextComponentSystem::TEXT)) {
		TextComponent& textComponent = entity.addComponent<TextComponent>();
		PositionComponent& positionComponent = entity.addComponent<PositionComponent>();
		Components components = { textComponent, positionComponent };
		this->components.push_back(components);

		std::string textValue = factory.stringValues.at(TextComponentSystem::TEXT);
		textComponent.setString(textValue);

		if (factory.boolValues.count(TextComponentSystem::DRAWN)) {
			bool drawnValue = factory.boolValues.at(TextComponentSystem::DRAWN);
			textComponent.setDrawn(drawnValue);
		}

		if (factory.floatValues.count(TextComponentSystem::OFFSET_X)) {
			textComponent.getOffset().x = factory.floatValues.at(TextComponentSystem::OFFSET_X);
		}
		
		if (factory.floatValues.count(TextComponentSystem::OFFSET_Y)) {
			textComponent.getOffset().y = factory.floatValues.at(TextComponentSystem::OFFSET_Y);
		}
	}

}


const std::string& TextComponentSystem::getName() {
	return TextComponentSystem::DRAWN;
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
