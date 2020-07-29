#include "objects/factories/TIEntityFactory.h"

#include <algorithm>

#include "componentsystems/EventsComponentSystem.h"
#include "componentsystems/GraphicsComponentSystem.h"
#include "componentsystems/GridComponentSystem.h"
#include "componentsystems/MovesComponentSystem.h"
#include "componentsystems/SelectableComponentSystem.h"
#include "managers/SceneManager.h"
#include "objects/components/EventsComponent.h"
#include "objects/components/GridComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/components/SelectableComponent.h"
#include "objects/components/TextComponent.h"
#include "objects/components/MovesComponent.h"
#include "objects/entities/TIEntity.h"

using namespace TIE;

TIEntityFactory::TIEntityFactory() {
	this->validComponentNames = {
			GraphicsComponentSystem::DRAWN,
			MovesComponentSystem::MOVES,
			SelectableComponentSystem::SELECTABLE,
			EventsComponentSystem::EVENTS,
			GridComponentSystem::GRID
		};
}

TIEntity& TIEntityFactory::build() {

	if (this->parent == nullptr) {
		this->parent = &SceneManager::Instance()->getClientLayer();
	}

	TIEntity& tientity = this->parent->attachChild();
	tientity.setName(this->name);

	SpriteComponent* spriteComponent = GraphicsComponentSystem::addSpriteComponent(*this, tientity);
	TextComponent* textComponent = GraphicsComponentSystem::addTextComponent(*this, tientity);
	MovesComponent* movesComponent = MovesComponentSystem::addMovesComponent(*this, tientity);
	SelectableComponent* selectableComponent = SelectableComponentSystem::addSelectableComponent(*this, tientity);
	EventsComponent* eventsComponent = EventsComponentSystem::addEventsComponent(*this, tientity);
	GridComponent* gridComponent = GridComponentSystem::addGridComponent(*this, tientity);

	return tientity;
}


TIEntityFactory& TIEntityFactory::setParent(TIEntity* parent) {
	this->parent = parent;
	return *this;
}

bool TIEntityFactory::isValidComponentName(const std::string& componentName) {
	return std::find(std::begin(this->validComponentNames), std::end(this->validComponentNames), componentName) != this->validComponentNames.end();
}


TIEntityFactory& TIEntityFactory::setName(std::string name) {
	this->name = name;
	return *this;
}
