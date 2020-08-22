#include "objects/factories/TIEntityFactory.h"

#include <algorithm>

#include "managers/SceneManager.h"
#include "componentsystems/AnimatedComponentSystem.h"
#include "componentsystems/CollidesComponentSystem.h"
#include "componentsystems/EventsComponentSystem.h"
#include "componentsystems/GridComponentSystem.h"
#include "componentsystems/MovesComponentSystem.h"
#include "componentsystems/SpriteComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"
#include "componentsystems/ShapeComponentSystem.h"
#include "objects/components/AnimatedComponent.h"
#include "objects/components/EventsComponent.h"
#include "objects/components/GridComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/components/TextComponent.h"
#include "objects/components/MovesComponent.h"
#include "objects/entities/TIEntity.h"

using namespace TIE;

TIEntityFactory::TIEntityFactory() {
	this->validComponentNames = {
			AnimatedComponentSystem::ANIMATED,
			SpriteComponentSystem::DRAWN,
			MovesComponentSystem::MOVES,
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

	SpriteComponentSystem::Instance()->addComponent(*this, tientity);
	TextComponentSystem::Instance()->addComponent(*this, tientity);
	ShapeComponentSystem::Instance()->addComponent(*this, tientity);
	GridComponentSystem::Instance()->addComponent(*this, tientity);
	MovesComponentSystem::Instance()->addComponent(*this, tientity);
	CollidesComponentSystem::Instance()->addComponent(*this, tientity);
	AnimatedComponentSystem::Instance()->addComponent(*this, tientity);
	EventsComponentSystem::Instance()->addComponent(*this, tientity);

	for (auto & child : this->children) {
		child.setParent(&tientity);
		child.build();
	}

	return tientity;
}


TIEntityFactory& TIEntityFactory::setParent(TIEntity* parent) {
	this->parent = parent;
	return *this;
}

TIEntityFactory& TIEntityFactory::registerChild() {
	this->children.push_back(TIEntityFactory());
	TIEntityFactory& child = this->children.back();
	return child;
}


bool TIEntityFactory::isValidComponentName(const std::string& componentName) {
	return std::find(std::begin(this->validComponentNames), std::end(this->validComponentNames), componentName) != this->validComponentNames.end();
}


TIEntityFactory& TIEntityFactory::setName(std::string name) {
	this->name = name;
	return *this;
}
