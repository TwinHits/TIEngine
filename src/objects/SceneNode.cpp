#include "managers/HashManager.h"
#include "managers/LogManager.h"
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


void SceneNode::draw(sf::RenderTarget& window, sf::RenderStates states) const {

	states.transform *= this->getTransform();

	if (this->getDrawn()) {
		this->drawSelf(window, states);

		for (auto& child : children) {
			child->draw(window, states);	
		}
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


SceneNode& SceneNode::attachChild(std::unique_ptr<SceneNode> child){
	LogManager::Instance()->logInfo("Attaching node with name " + child->getName() +  ".");
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


bool SceneNode::operator==(const SceneNode& rhs) const {
	const SceneNode* ptr = &rhs;
	return this == ptr;
}


bool SceneNode::operator!=(const SceneNode& rhs) const {
	const SceneNode* ptr = &rhs;
	return this != ptr;
}
