#include "objects/tientities/TIEntity.h"

#include <memory>

#include "managers/HashManager.h"
#include "managers/SceneManager.h"
#include "managers/WorldManager.h"

using namespace TIE;

TIEntity::TIEntity() {
	this->id = HashManager::Instance()->getNewGlobalId();
	WorldManager::Instance()->registerTIEntity(*this);
}

TIEntity::~TIEntity() {}


GlobalId TIEntity::getId() const {
	return this->id;
}


void TIEntity::setParent(TIEntity* parent) {
	this->parent = parent;
}


TIEntity& TIEntity::getParent() {
	return *(this->parent);
}


bool TIEntity::hasParent() {
	return this->parent != nullptr;
}


bool TIEntity::hasChildren() {
	return !this->children.empty();
}


std::vector<std::unique_ptr<TIEntity> >& TIEntity::getChildren() {
	return this->children;
}


void TIEntity::setRemove(bool remove) {
	SceneManager::Instance()->setTIEntitiesMarkedForRemove(true);
	this->remove = remove;
	this->setRemoveChildren(remove);
}


void TIEntity::setRemoveChildren(bool remove) {
	for (auto child = children.begin(); child != children.end(); ++child) {
		(*child)->setRemove(remove);
	}
}


bool TIEntity::getRemove() const {
	return this->remove;
}


void TIEntity::setName(const std::string& name) {
	this->name = name;
}


const std::string& TIEntity::getName() const {
	return this->name;
}


TIEntity& TIEntity::attachChild(std::unique_ptr<TIEntity> child) {
	child->setParent(this);
	this->children.push_back(std::move(child));
	return *children.back();
}


TIEntity& TIEntity::attachChild() {
	this->children.push_back(make_unique<TIEntity>());
	TIEntity& child = *children.back();
	child.setParent(this);
	return child;
}


bool TIEntity::isSceneLayer() {
	return false;
}


bool TIEntity::isRelatedTo(TIEntity& rhs) {
	TIEntity* parentClosestToSceneLayer = this;
	while (parentClosestToSceneLayer->hasParent() && !parentClosestToSceneLayer->getParent().isSceneLayer()) {
		parentClosestToSceneLayer = &parentClosestToSceneLayer->getParent();
	}
	return parentClosestToSceneLayer->isParentOf(rhs);
}


bool TIEntity::isParentOf(TIEntity& rhs) {
	for (auto& child : this->getChildren()) {
		if (*child == rhs || child->isParentOf(rhs)) {
			return true;
		}
	}
	return false;
}


std::unique_ptr<TIEntity> TIEntity::detachChild(const TIEntity& child) {
	for (auto c = this->children.begin(); c != this->children.end(); ++c) {
		if (*(*c) == child) {
			std::unique_ptr<TIEntity> result = std::move(*c);
			result->setParent(nullptr);
			this->children.erase(c);
			return result;
		}
	}

	return nullptr;
}


bool TIEntity::operator==(const TIEntity& rhs) const {
	return this->getId() == rhs.getId();
}


bool TIEntity::operator!=(const TIEntity& rhs) const {
	if (*this == rhs) {
		return false;
	}
	return true;
}


void TIEntity::operator=(const TIEntity&) {

}
