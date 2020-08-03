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
const std::string GraphicsComponentSystem::TEXTURE_KEY = GraphicsComponentSystem::DRAWN + '.' + GraphicsComponentSystem::TEXTURE;
const std::string GraphicsComponentSystem::DRAWN_KEY = GraphicsComponentSystem::DRAWN + '.' + GraphicsComponentSystem::DRAWN;
const std::string GraphicsComponentSystem::TEXT_KEY = GraphicsComponentSystem::DRAWN + '.' + GraphicsComponentSystem::TEXT;

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


SpriteComponent& GraphicsComponentSystem::addSpriteComponent(TIEntity& entity) {
	return entity.addComponent<SpriteComponent>();
}


SpriteComponent* GraphicsComponentSystem::addSpriteComponent(const TIEntityFactory& factory, TIEntity& entity) {

	SpriteComponent* spritePtr = nullptr;
	if (factory.stringValues.count(GraphicsComponentSystem::TEXTURE_KEY)) {
		std::string textureName = factory.stringValues.at(GraphicsComponentSystem::TEXTURE_KEY);
		const sf::Texture& texture = AssetsManager::Instance()->getTexture(textureName);
		SpriteComponent& spriteComponent = entity.addComponent<SpriteComponent>();
		spriteComponent.setTexture(texture, true);
		sf::FloatRect size = spriteComponent.getLocalBounds();
		spriteComponent.setOrigin(size.width/2, size.height/2);

		if (factory.boolValues.count(GraphicsComponentSystem::DRAWN_KEY)) {
			bool drawn = factory.boolValues.at(GraphicsComponentSystem::DRAWN_KEY);
			spriteComponent.setDrawn(drawn);
		}
		spritePtr = &spriteComponent;
	}

	return spritePtr;
}


TextComponent& GraphicsComponentSystem::addTextComponent(TIEntity& entity) {
	return entity.addComponent<TextComponent>();
}

TextComponent* GraphicsComponentSystem::addTextComponent(const TIEntityFactory& factory, TIEntity& entity) {

	TextComponent* textPtr = nullptr;
	if (factory.stringValues.count(GraphicsComponentSystem::TEXT_KEY)) {
		std::string textValue = factory.stringValues.at(GraphicsComponentSystem::TEXT_KEY);
		TextComponent& textComponent = entity.addComponent<TextComponent>();
		textComponent.setString(textValue);

		if (factory.boolValues.count(GraphicsComponentSystem::DRAWN_KEY)) {
			bool drawnValue = factory.boolValues.at(GraphicsComponentSystem::DRAWN_KEY);
			textComponent.setDrawn(drawnValue);
		}

		textPtr = &textComponent;
	}

	return textPtr;
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
