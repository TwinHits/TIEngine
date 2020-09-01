#include "componentsystems/TextComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/TextComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/AssetsManager.h"
#include "utils/StringHelpers.h"

using namespace TIE;

const std::string TextComponentSystem::DRAWN = "draw.drawn";
const std::string TextComponentSystem::TEXT = "drawn.text";

void TextComponentSystem::update(const float delta) {
	for (auto& c : this->components) {	

	}
}

TextComponent& TextComponentSystem::addComponent(TIEntity& entity) {
	return entity.addComponent<TextComponent>();
}

void TextComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& entity) {

	if (factory.stringValues.count(TextComponentSystem::TEXT)) {
		std::string textValue = factory.stringValues.at(TextComponentSystem::TEXT);
		TextComponent& textComponent = entity.addComponent<TextComponent>();
		textComponent.setString(textValue);

		if (factory.boolValues.count(TextComponentSystem::DRAWN)) {
			bool drawnValue = factory.boolValues.at(TextComponentSystem::DRAWN);
			textComponent.setDrawn(drawnValue);
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
