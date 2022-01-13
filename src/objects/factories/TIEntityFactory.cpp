#include "objects/factories/TIEntityFactory.h"

#include <algorithm>

#include "componentsystems/ComponentSystem.h"
#include "componentsystems/LifecycleComponentSystem.h"
#include "managers/SceneManager.h"
#include "managers/WorldManager.h"
#include "objects/entities/TIEntity.h"

using namespace TIE;

TIEntity& TIEntityFactory::build() {

	if (this->stringValues.count(TIEntityFactory::NAME)) {
		this->name = this->stringValues.at(TIEntityFactory::NAME);
	}

	if (this->parent == nullptr) {
		this->parent = &SceneManager::Instance()->getClientLayer();
	}

	TIEntity& tientity = this->parent->attachChild();
	tientity.setName(this->name);

	for (ComponentSystem* componentSystem : SceneManager::Instance()->getComponentSystems()) {
		if (this->componentSystemNames.count(componentSystem->getName())) {
			componentSystem->addComponent(*this, tientity);
		}
	}

	LifecycleComponentSystem::Instance()->runCreated(tientity);

	for (auto & child : this->children) {
		child.setParent(&tientity);
		child.build();
	}

	WorldManager::Instance()->registerTIEntity(tientity);
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
