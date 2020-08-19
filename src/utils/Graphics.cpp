#include "utils/Graphics.h"

#include "objects/components/ShapeComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/components/TextComponent.h"
#include "objects/entities/TIEntity.h"

void TIE::Graphics::setDrawn(TIEntity& entity, const bool drawn) {
	
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


const bool TIE::Graphics::isDrawn(TIEntity& entity) {

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

