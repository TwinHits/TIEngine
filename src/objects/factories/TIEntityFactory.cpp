#include "objects/factories/TIEntityFactory.h"

#include <sol/sol.hpp>

#include <algorithm>

#include "componentsystems/ComponentSystem.h"
#include "componentsystems/LifecycleComponentSystem.h"
#include "componentsystems/WireframeComponentSystem.h"
#include "managers/ComponentSystemsManager.h"
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
	if (this->getShowWireframe()) {
		this->addComponentSystemByComponentName(WireframeComponentSystem::Instance()->getName());
	}

	if (this->parent == nullptr) {
		this->setParent(&SceneManager::Instance()->getClientLayer());
	}

	TIEntity& tientity = this->parent->attachChild();
	tientity.setName(this->name);

	for (ComponentSystem* componentSystem : ComponentSystemsManager::Instance()->getComponentSystems()) {
		if (this->componentSystemNames.count(componentSystem->getName())) {
			componentSystem->addComponent(*this, tientity);
		}
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
	if (ComponentSystemsManager::Instance()->isValidComponentName(name)) {
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


const bool TIEntityFactory::getShowWireframe() const {
	return this->showWireframe;
}


void TIEntityFactory::setShowWireFrame(const bool showWireframe) {
	this->showWireframe = showWireframe;
}
