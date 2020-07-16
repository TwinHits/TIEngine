#include "objects/factories/TIEntityFactory.h"

#include "managers/AssetsManager.h"
#include "managers/LogManager.h"
#include "managers/SceneManager.h"
#include "objects/components/SpriteComponent.h"
#include "objects/components/SelectableComponent.h"
#include "objects/components/TextComponent.h"
#include "objects/components/MovesComponent.h"
#include "objects/entities/TIEntity.h"

using namespace TIE;

const std::string TIEntityFactory::DRAWN = "drawn";
const std::string TIEntityFactory::TEXTURE = "texture";
const std::string TIEntityFactory::TEXT = "text";
const std::string TIEntityFactory::MOVES = "moves";
const std::string TIEntityFactory::SPEED = "speed";
const std::string TIEntityFactory::DIRECTION = "direction";
const std::string TIEntityFactory::SELECTABLE = "selectable";

TIEntity& TIEntityFactory::build() {

	if (this->parent == nullptr) {
		this->parent = &SceneManager::Instance()->getClientLayer();
	}

	TIEntity& tientity = this->parent->attachChild();

	if (this->hasSprite) {
		SpriteComponent* spriteComponent = tientity.addComponent<SpriteComponent>();
		spriteComponent->setDrawn(this->isDrawn);
		const sf::Texture& texture = AssetsManager::Instance()->getTexture(this->texture);
		spriteComponent->setTexture(texture);
		spriteComponent->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(texture.getSize())));
	}

	if (this->hasText) {
		TextComponent* textComponent = tientity.addComponent<TextComponent>();
		textComponent->setDrawn(this->isDrawn);
		textComponent->setString(this->text);
	}

	if (this->hasMoves) {
		MovesComponent* movesComponent = tientity.addComponent<MovesComponent>();
		movesComponent->setVelocity(sf::Vector2f(this->speed, this->direction));
		if (!this->hasSprite) {
			LogManager::Instance()->warn("Entity " + this->name + " has a move component but no sprite component.");
		}
	}

	if (this->hasSelectable) {
		SelectableComponent* selectableComponent = tientity.addComponent<SelectableComponent>();
		selectableComponent->setSelectable(this->isSelectable);
	}

	return tientity;
}

TIEntityFactory& TIEntityFactory::setParent(TIEntity* parent) {
	this->parent = parent;
	return *this;
}

TIEntityFactory& TIEntityFactory::setName(std::string name) {
	this->name = name;
	return *this;
}

TIEntityFactory& TIEntityFactory::setDrawn(bool drawn) {
	this->isDrawn = drawn;
	return *this;
}


TIEntityFactory& TIEntityFactory::setTexture(const std::string& texture) {
	this->texture = texture;
	this->hasSprite = true;
	return *this;
}


TIEntityFactory& TIEntityFactory::setText(const std::string& text) {
	this->text = text;
	this->hasText = true;
	return *this;
}


TIEntityFactory& TIEntityFactory::setSpeed(const float speed) {
	this->speed = speed;
	this->hasMoves = true;
	return *this;
}


TIEntityFactory& TIEntityFactory::setDirection(const float direction) {
	this->direction = direction;
	this->hasMoves = true;
	return *this;
}

TIEntityFactory& TIEntityFactory::setSelectable(const bool selectable) {
	this->isSelectable = selectable;
	this->hasSelectable = true;
	return *this;
}

