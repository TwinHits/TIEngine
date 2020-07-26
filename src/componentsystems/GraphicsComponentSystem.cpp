#include "componentsystems/GraphicsComponentSystem.h" 

#include <SFML/Graphics.hpp>

#include "objects/components/ShapeComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/components/TextComponent.h"

using namespace TIE;

void GraphicsComponentSystem::draw(TIEntity& entity, sf::RenderTarget& window, sf::RenderStates states) {
	SpriteComponent* spriteComponent = entity.getComponent<SpriteComponent>();
	TextComponent* textComponent = entity.getComponent<TextComponent>();
	ShapeComponent* shapeComponent = entity.getComponent<ShapeComponent>();
	
	//Continue traversal if there's no graphics components, or if either component is drawn
	bool continueTraversal = textComponent == nullptr && spriteComponent == nullptr && shapeComponent == nullptr;
	if (spriteComponent != nullptr && spriteComponent->isDrawn()) {
		//states.transform *= spriteComponent->getTransform();
		window.draw(*dynamic_cast<sf::Sprite*>(spriteComponent), states);
		continueTraversal = true;
	}

	if (textComponent != nullptr && textComponent->isDrawn()) {
		window.draw(*dynamic_cast<sf::Text*>(textComponent));
		continueTraversal = true;
	}

	if (shapeComponent != nullptr && shapeComponent->isDrawn()) {
		window.draw(*dynamic_cast<sf::Shape*>(shapeComponent));
		continueTraversal = true;
	}

	if (continueTraversal) {
		for (auto& child : entity.getChildren()) {
			GraphicsComponentSystem::draw(*child, window, states);
		}
	}
}


 SpriteComponent* GraphicsComponentSystem::addSpriteComponent(TIEntity& entity) {
	return entity.addComponent<SpriteComponent>();
}


TextComponent* GraphicsComponentSystem::addTextComponent(TIEntity& entity) {
	return entity.addComponent<TextComponent>();
}


void GraphicsComponentSystem::setDrawn(TIEntity& entity, bool drawn) {
	
	SpriteComponent* spriteComponent = entity.getComponent<SpriteComponent>();
	if (spriteComponent != nullptr) {
		spriteComponent->setDrawn(drawn);
	}

	TextComponent* textComponent = entity.getComponent<TextComponent>();
	if (textComponent != nullptr) {
		textComponent->setDrawn(drawn);
	}

	ShapeComponent* shapeComponent = entity.getComponent<ShapeComponent>();
	if (shapeComponent != nullptr) {
		shapeComponent->setDrawn(drawn);
	}
}

bool GraphicsComponentSystem::isDrawn(TIEntity& entity) {
	
	SpriteComponent* spriteComponent = entity.getComponent<SpriteComponent>();
	if (spriteComponent != nullptr && spriteComponent->isDrawn()) {
		return spriteComponent->isDrawn();
	}

	TextComponent* textComponent = entity.getComponent<TextComponent>();
	if (textComponent != nullptr && textComponent->isDrawn()) {
		return textComponent->isDrawn();
	}

	ShapeComponent* shapeComponent = entity.getComponent<ShapeComponent>();
	if (shapeComponent != nullptr && shapeComponent->isDrawn()) {
		return shapeComponent->isDrawn();
	}

	return false;
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
