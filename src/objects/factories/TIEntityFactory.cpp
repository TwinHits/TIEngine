#include "objects/factories/TIEntityFactory.h"

#include "managers/AssetsManager.h"
#include "managers/LogManager.h"
#include "managers/SceneManager.h"
#include "objects/components/EventsComponent.h"
#include "objects/components/GridComponent.h"
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
const std::string TIEntityFactory::EVENTS = "events";
const std::string TIEntityFactory::SELECTED = "selected";
const std::string TIEntityFactory::CLICK = "click";

TIEntity& TIEntityFactory::build() {

	if (this->parent == nullptr) {
		this->parent = &SceneManager::Instance()->getClientLayer();
	}

	TIEntity& tientity = this->parent->attachChild();

	if (this->hasSprite) {
		SpriteComponent* spriteComponent = tientity.addComponent<SpriteComponent>();
		spriteComponent->setDrawn(this->isDrawn);
		const sf::Texture& texture = AssetsManager::Instance()->getTexture(this->texture);
		spriteComponent->setTexture(texture, true);
		sf::FloatRect size = spriteComponent->getLocalBounds();
		spriteComponent->setOrigin(size.width/2, size.height/2);
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
		if (!this->hasSprite) {
			LogManager::Instance()->warn("Entity " + this->name + " has a selectable component but no sprite component.");
		}
	}

	if (this->hasEvents) {
		EventsComponent* eventsComponent = tientity.addComponent<EventsComponent>();
		eventsComponent->setClick(this->click);
	}

	if (this->hasGrid) {
		GridComponent* gridComponent = tientity.addComponent<GridComponent>();
		gridComponent->setGridSize(this->gridSize);
		SpriteComponent* spriteComponent = tientity.getComponent<SpriteComponent>();
		sf::FloatRect textureSize = spriteComponent->getLocalBounds();
		gridComponent->setTileSize(sf::Vector2f(textureSize.width / this->gridSize.x, textureSize.height / this->gridSize.y));
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


TIEntityFactory& TIE::TIEntityFactory::setClick(const std::string& click) {
	this->click = click;
	this->hasEvents = true;
	return *this;
}


TIEntityFactory& TIE::TIEntityFactory::setGridSize(sf::Vector2i gridSize) {
	this->gridSize = gridSize;
	this->hasGrid = true;
	return *this;
}
