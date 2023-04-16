#include "objects/factories/TIEntityFactory.h"

#include <sol/sol.hpp>

#include <algorithm>

#include "componentsystems/ComponentSystem.h"
#include "componentsystems/LifecycleComponentSystem.h"
#include "componentsystems/LineComponentSystem.h"
#include "componentsystems/ShapeComponentSystem.h"
#include "componentsystems/SpriteComponentSystem.h"
#include "componentsystems/TextComponentSystem.h"
#include "managers/SceneManager.h"
#include "managers/ScriptManager.h"
#include "managers/WorldManager.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

TIEntityFactory::TIEntityFactory(const sol::table& definition) {
    ScriptManager::Instance()->loadTIEntityDefinition(*this, definition);
}


TIEntity& TIEntityFactory::build() {

	if (this->stringValues.count(TIEntityFactory::NAME)) {
		this->setName(this->stringValues.at(TIEntityFactory::NAME));
	}

	if (this->boolValues.count(TIEntityFactory::SHOW_WIREFRAME)) {
		this->setShowWireFrame(this->boolValues.at(TIEntityFactory::SHOW_WIREFRAME));
	}

	if (this->parent == nullptr) {
		this->setParent(&SceneManager::Instance()->getClientLayer());
	}

	TIEntity& tientity = this->parent->attachChild();
	tientity.setName(this->name);

	for (ComponentSystem* componentSystem : SceneManager::Instance()->getComponentSystems()) {
		if (this->componentSystemNames.count(componentSystem->getName())) {
			componentSystem->addComponent(*this, tientity);
		}
	}

	if (this->showWireframe) {
		// This should be handled better. 
		// Probably move showWireframe back to the component systems
		SpriteComponentSystem::Instance()->addWireframe(tientity);
		TextComponentSystem::Instance()->addWireframe(tientity);
		LineComponentSystem::Instance()->addWireframe(tientity);
	}

	LifecycleComponentSystem::Instance()->runCreated(tientity);

	for (auto & child : this->children) {
		child.setParent(&tientity);
		child.setShowWireFrame(this->getShowWireframe());
		child.build();
	}

	WorldManager::Instance()->registerTIEntity(tientity);
    WorldManager::Instance()->saveTIEntityFactory(tientity.getName(), *this);
	return tientity;
}


TIEntityFactory& TIEntityFactory::addComponentSystemByComponentName(const std::string& name) {
	if (SceneManager::Instance()->isValidComponentName(name)) {
		this->componentSystemNames[name] = true;
	}
	return *this;
}


TIEntityFactory& TIEntityFactory::setParent(TIEntity* parent) {
	this->parent = parent;
	return *this;
}


TIEntityFactory& TIEntityFactory::addChild() {
	this->children.push_back(TIEntityFactory());
	TIEntityFactory& child = this->children.back();
	return child;
}


TIEntityFactory& TIEntityFactory::setName(std::string name) {
	this->name = name;
	return *this;
}


const std::string& TIEntityFactory::getName() {
	return this->name;
}


const bool TIEntityFactory::getShowWireframe() {
	return this->showWireframe;
}


void TIEntityFactory::setShowWireFrame(const bool showWireframe) {
	this->showWireframe = showWireframe;
}
