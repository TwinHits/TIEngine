#include <memory>

#include "objects/entities/TIEntity.h"
#include "managers/HashManager.h"
#include <functional>

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


const std::vector<std::unique_ptr<TIEntity> >& TIEntity::getChildren() const {
	return this->children;
}


void TIEntity::setRemove(bool remove) {
	this->remove = remove;
}


bool TIEntity::getRemove() const {
	return this->remove;
}


void TIEntity::removeNodes() {
	//This probably can cut out if removal is successful
	auto removesBegin = std::remove_if(this->children.begin(), this->children.end(), std::mem_fn(&TIEntity::getRemove));
	this->children.erase(removesBegin, this->children.end());
	std::for_each(this->children.begin(), this->children.end(), std::mem_fn(&TIEntity::removeNodes));
}


TIEntity& TIEntity::attachChild(std::unique_ptr<TIEntity> child) {
	child->setParent(this);
	children.push_back(std::move(child));
	return *children.back();
}


std::unique_ptr<TIEntity> TIEntity::detachChild(const TIEntity& child) {
	for (auto c = children.begin(); c != children.end(); ++c) {
		if (*(*c) == child) {
			std::unique_ptr<TIEntity> result = std::move(*c);
			result->setParent(nullptr);
			children.erase(c);
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


/*
TIEntity* TIEntity::findNode(sf::Vector2f point) {
	if (this->getHitBox().contains(point)) {
		return this;
	} else {
		for (auto& child : children) {
			TIEntity* ptr = child->findNode(point);
			if (ptr != nullptr) {
				return ptr;
			}
		}
		return nullptr;
	}
}
*/
