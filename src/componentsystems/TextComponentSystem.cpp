#include "componentsystems/TextComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/TextComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/AssetsManager.h"
#include "utilities/StringHelpers.h"

using namespace TIE;

const std::string TextComponentSystem::DRAWN = "drawn";
const std::string TextComponentSystem::TEXT = "text";
const std::string TextComponentSystem::DRAWN_KEY = TextComponentSystem::DRAWN + '.' + TextComponentSystem::DRAWN;
const std::string TextComponentSystem::TEXT_KEY = TextComponentSystem::DRAWN + '.' + TextComponentSystem::TEXT;

void TextComponentSystem::update(TIEntity& tientity, const float delta) {

}

TextComponent& TextComponentSystem::addComponent(TIEntity& entity) {
	return entity.addComponent<TextComponent>();
}

void TextComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& entity) {

	TextComponent* textPtr = nullptr;
	if (factory.stringValues.count(TextComponentSystem::TEXT_KEY)) {
		std::string textValue = factory.stringValues.at(TextComponentSystem::TEXT_KEY);
		TextComponent& textComponent = entity.addComponent<TextComponent>();
		textComponent.setString(textValue);

		if (factory.boolValues.count(TextComponentSystem::DRAWN_KEY)) {
			bool drawnValue = factory.boolValues.at(TextComponentSystem::DRAWN_KEY);
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
