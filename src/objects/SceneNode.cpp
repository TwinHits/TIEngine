#include "managers/HashManager.h"
#include "objects/SceneNode.h" 
using namespace TIE;

SceneNode::SceneNode() {
	this->id = HashManager::Instance()->getNewGlobalId();
}

SceneNode::~SceneNode() { 
} 


SceneNode::SceneNode(const SceneNode&) {


}


GlobalId SceneNode::getId() const {
	return this->id;
}


void SceneNode::setName(const std::string& name) {
	this->name = name;
}


std::string SceneNode::getName() const {
	return this->name;
}


void SceneNode::setDrawn(bool drawn) {
	this->drawn = drawn;
}


bool SceneNode::getDrawn() const {
	return this->drawn;
}


void SceneNode::setCollidable(bool collidable) { 
	this->collidable = collidable;
}


bool SceneNode::getCollidable() const { 
	return this->collidable; 
}


void SceneNode::setParent(SceneNode* parent) {
	this->parent = parent;
}


SceneNode& SceneNode::getParent() {
	return *parent;
}


sf::Vector2f SceneNode::getWorldPosition() const {
	return this->getWorldTransform() * sf::Vector2f();
}


float SceneNode::getWorldRotation() const {
	float rotation = 0;

	for (SceneNode* n = parent; n != nullptr; n = n->parent) {
		rotation+=n->getRotation();
	}

	return rotation;
}


void SceneNode::checkSceneCollisions(SceneNode& sceneGraphRoot, std::set<std::pair<SceneNode*, SceneNode*> >& collisions) {
	this->checkNodeCollisions(sceneGraphRoot, collisions);
	for (auto& child : sceneGraphRoot.children) {
		this->checkSceneCollisions(*child, collisions);
	}	
}


void SceneNode::checkNodeCollisions(SceneNode& sceneNode, std::set<std::pair<SceneNode*, SceneNode*> >& collisions) {
	if (*this != sceneNode && collision(*this, sceneNode)) {
		collisions.insert(std::minmax(this, &sceneNode));
	}
	for (auto& child : this->children) {
		child->checkNodeCollisions(sceneNode, collisions);
	}	
}


void SceneNode::update(const float delta) {

	this->updateSelf(delta);

	for (auto& child : this->children) {
		if (child != nullptr) {
			child->update(delta);
		}
	}
}


void SceneNode::draw(sf::RenderTarget& window, sf::RenderStates states) const {

	states.transform *= this->getTransform();

	if (this->getDrawn()) {
		this->drawSelf(window, states);

		for (auto& child : children) {
			child->draw(window, states);	
		}
	}
}


SceneNode& SceneNode::attachChild(std::unique_ptr<SceneNode> child){
	child->setParent(this);
	children.push_back(std::move(child));
	return *children.back();
}


std::unique_ptr<SceneNode> SceneNode::detachChild(const SceneNode& child){
	for (auto c = children.begin(); c != children.end(); ++c) {
		if (*(*c) == child) {
			std::unique_ptr<SceneNode> result = std::move(*c);
			result->setParent(nullptr);
			children.erase(c);
			return result;
		}
	}

	return nullptr;
}


sf::Transform SceneNode::getWorldTransform() const {
	sf::Transform transform = sf::Transform::Identity;

	for (SceneNode* n = parent; n != nullptr; n = n->parent) {
		transform = n->getTransform() * transform;
	}

	return transform;
}


bool SceneNode::collision(SceneNode& lhs, SceneNode& rhs) const {
	if (!lhs.getCollidable() || !rhs.getCollidable()) {
		return false;
	}
	return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}


sf::FloatRect SceneNode::getBoundingRect() const {
	return sf::FloatRect(0, 0, 0, 0);
}


bool SceneNode::operator==(const SceneNode& rhs) const {
	if (this->getId() == rhs.getId()) {
		return true;
	}
	return false;
}


bool SceneNode::operator!=(const SceneNode& rhs) const {
	if (*this == rhs) {
		return false;
	}
	return true;
}
