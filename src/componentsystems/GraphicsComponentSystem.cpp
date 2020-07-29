#include "componentsystems/GraphicsComponentSystem.h" 

#include <string>

#include <SFML/Graphics.hpp>

#include "objects/components/ShapeComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/components/TextComponent.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"
#include "managers/AssetsManager.h"

using namespace TIE;

const std::string GraphicsComponentSystem::DRAWN = "drawn";
const std::string GraphicsComponentSystem::TEXTURE = "texture";
const std::string GraphicsComponentSystem::TEXT = "text";

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


SpriteComponent* GraphicsComponentSystem::addSpriteComponent(const TIEntityFactory& factory, TIEntity& entity) {
	SpriteComponent* spriteComponent = nullptr;
	auto drawnValue = factory.boolValues.find("drawn.drawn");
	auto textureValue = factory.stringValues.find("drawn.texture");

	if (textureValue != factory.stringValues.end()) {
		if (spriteComponent == nullptr) {
			spriteComponent = entity.addComponent<SpriteComponent>();
		}
		const sf::Texture& texture = AssetsManager::Instance()->getTexture(textureValue->second);
		spriteComponent->setTexture(texture, true);
		sf::FloatRect size = spriteComponent->getLocalBounds();
		spriteComponent->setOrigin(size.width/2, size.height/2);
	}

	if (spriteComponent != nullptr && drawnValue != factory.boolValues.end()) {
		spriteComponent->setDrawn(drawnValue->second);
	}

	return spriteComponent;
}


TextComponent* GraphicsComponentSystem::addTextComponent(TIEntity& entity) {
	return entity.addComponent<TextComponent>();
}

TextComponent* GraphicsComponentSystem::addTextComponent(const TIEntityFactory& factory, TIEntity& entity) {
	TextComponent* textComponent = nullptr;
	auto drawnValue = factory.boolValues.find("drawn.drawn");
	auto textValue = factory.stringValues.find("drawn.text");

	if (textValue != factory.stringValues.end()) {
		if (textComponent == nullptr) {
			textComponent = entity.addComponent<TextComponent>();
		}
		textComponent->setString(textValue->second);
	}

	if (textComponent != nullptr && drawnValue != factory.boolValues.end()) {
		textComponent->setDrawn(drawnValue->second);
	}

	return textComponent;
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
