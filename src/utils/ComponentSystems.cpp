#include "utils/ComponentSystems.h"

#include "objects/components/TextComponent.h"
#include "objects/components/ShapeComponent.h"
#include "objects/components/SpriteComponent.h"

using namespace TIE;

void ComponentSystems::setDrawn(TIEntity& entity, const bool drawn) {

	TextComponent* textComponent = entity.getComponent<TextComponent>();
	SpriteComponent* spriteComponent = entity.getComponent<SpriteComponent>();
	ShapeComponent* shapeComponent = entity.getComponent<ShapeComponent>();

	if (textComponent != nullptr) {
		textComponent->setDrawn(drawn);
	}

	if (spriteComponent != nullptr) {
		spriteComponent->setDrawn(drawn);
	}

	if (shapeComponent != nullptr) {
		shapeComponent->setDrawn(drawn);
	}
}


bool ComponentSystems::isDrawn(TIEntity& entity) {

	TextComponent* textComponent = entity.getComponent<TextComponent>();
	SpriteComponent* spriteComponent = entity.getComponent<SpriteComponent>();
	ShapeComponent* shapeComponent = entity.getComponent<ShapeComponent>();

	if (textComponent != nullptr && textComponent->isDrawn()) {
		return textComponent->isDrawn();
	}

	if (spriteComponent != nullptr && spriteComponent->isDrawn()) {
		return spriteComponent->isDrawn();
	}

	if (shapeComponent != nullptr && shapeComponent->isDrawn()) {
		return shapeComponent->isDrawn();
	}

	return false;
}

const sf::FloatRect ComponentSystems::getGlobalBounds(TIEntity& tientity) {

	SpriteComponent* spriteComponent = tientity.getComponent<SpriteComponent>();
	if (spriteComponent != nullptr && spriteComponent->isDrawn()) {
		return spriteComponent->getGlobalBounds();
	}

	TextComponent* textComponent = tientity.getComponent<TextComponent>();
	if (textComponent != nullptr && textComponent->isDrawn()) {
		return textComponent->getGlobalBounds();
	}

	ShapeComponent* shapeComponent = tientity.getComponent<ShapeComponent>();
	if (shapeComponent != nullptr && shapeComponent->isDrawn()) {
		for (auto& [id, shape] : shapeComponent->getShapes()) {
			return shape->getGlobalBounds();
		}
	}

	return sf::FloatRect(-1, 0, 0, 0);
}


const sf::FloatRect ComponentSystems::getLocalBounds(TIEntity& tientity) {

	ShapeComponent* shapeComponent = tientity.getComponent<ShapeComponent>();
	if (shapeComponent != nullptr && shapeComponent->isDrawn()) {
		for (auto& [id, shape] : shapeComponent->getShapes()) {
			return shape->getLocalBounds();
		}
	}

	SpriteComponent* spriteComponent = tientity.getComponent<SpriteComponent>();
	if (spriteComponent != nullptr && spriteComponent->isDrawn()) {
		return spriteComponent->getLocalBounds();
	}

	TextComponent* textComponent = tientity.getComponent<TextComponent>();
	if (textComponent != nullptr && textComponent->isDrawn()) {
		return textComponent->getLocalBounds();
	}

	return sf::FloatRect(-1, 0, 0, 0);
}


bool ComponentSystems::doesGlobalBoundsContain(TIEntity& tientity, const sf::Vector2f& position) {
	ShapeComponent* shapeComponent = tientity.getComponent<ShapeComponent>();
	if (shapeComponent != nullptr && shapeComponent->isDrawn()) {
		for (auto& [id, shape] : shapeComponent->getShapes()) {
			if (shape->getGlobalBounds().contains(position)) {
				return true;
			}
		}
	}

	SpriteComponent* spriteComponent = tientity.getComponent<SpriteComponent>();
	if (spriteComponent != nullptr && spriteComponent->isDrawn()) {
		if (spriteComponent->getGlobalBounds().contains(position)) {
			return true;
		}
	}

	TextComponent* textComponent = tientity.getComponent<TextComponent>();
	if (textComponent != nullptr && textComponent->isDrawn()) {
		if (textComponent->getGlobalBounds().contains(position)) {
			return true;
		}
	}

	return false;
}


