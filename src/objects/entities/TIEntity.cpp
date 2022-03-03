#include "objects/entities/TIEntity.h"

#include <memory>

#include "managers/HashManager.h"
#include "managers/SceneManager.h"
#include "templates/MakeUnique.h"

using namespace TIE;

TIEntity::TIEntity() {
	this->id = HashManager::Instance()->getNewGlobalId();
}


GlobalId TIEntity::getId() const {
	return this->id;
}


void TIEntity::setParent(TIEntity* parent) {
	this->parent = parent;
}


TIEntity& TIEntity::getParent() {
	return *parent;
}


std::vector<std::unique_ptr<TIEntity> >& TIEntity::getChildren() {
	return this->children;
}


void TIEntity::setRemove(bool remove) {
	SceneManager::Instance()->setTIEntitiesMarkedForRemove(true);
	this->remove = remove;
}


bool TIEntity::getRemove() const {
	return this->remove;
}


void TIEntity::setName(std::string name) {
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
