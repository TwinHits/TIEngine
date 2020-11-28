#include "objects/factories/TIEntityFactory.h"

#include <algorithm>

#include "componentsystems/ComponentSystem.h"
#include "managers/SceneManager.h"
#include "objects/entities/TIEntity.h"

using namespace TIE;

TIEntityFactory::TIEntityFactory() {
	for (ComponentSystem* componentSystem : SceneManager::Instance()->getComponentSystems()) {
		this->validComponentNames.push_back(componentSystem->getName());
	}
}


TIEntity& TIEntityFactory::build() {

	if (this->parent == nullptr) {
		this->parent = &SceneManager::Instance()->getClientLayer();
	}

	TIEntity& tientity = this->parent->attachChild();
	tientity.setName(this->name);

	for (ComponentSystem* componentSystem : SceneManager::Instance()->getComponentSystems()) {
		componentSystem->addComponent(*this, tientity);
	}

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
