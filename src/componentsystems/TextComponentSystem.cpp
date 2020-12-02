#include "componentsystems/TextComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/TextComponent.h"
#include "objects/components/PositionComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "utils/ComponentSystems.h"

using namespace TIE;

void TextComponentSystem::update(const float delta) {
	for (auto& c : this->components) {	
		c.textComponent.setPosition(c.positionComponent.position + c.textComponent.getOffset());
	}
}


void TextComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& entity) {

	std::string text = ComponentSystems::getFactoryValue<std::string>(factory, TextComponentSystem::TEXT, "", entity);
	bool drawn = ComponentSystems::getFactoryValue<bool>(factory, TextComponentSystem::DRAWN, false, entity);
	float offsetX = ComponentSystems::getFactoryValue<float>(factory, TextComponentSystem::OFFSET_X, 0.0f, entity);
	float offsetY = ComponentSystems::getFactoryValue<float>(factory, TextComponentSystem::OFFSET_Y, 0.0f, entity);

	if (!text.empty()) {
		TextComponent& textComponent = entity.addComponent<TextComponent>();
		PositionComponent& positionComponent = entity.addComponent<PositionComponent>();
		Components components = { textComponent, positionComponent };

		textComponent.setString(text);
		textComponent.setDrawn(drawn);
		textComponent.setOffset(sf::Vector2f(offsetX, offsetY));

		this->components.push_back(components);
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
