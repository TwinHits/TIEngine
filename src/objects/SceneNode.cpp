#include "objects/SceneNode.h"

using namespace TIE;

SceneNode::SceneNode() {

}


SceneNode::~SceneNode() {

}


SceneNode::SceneNode(const SceneNode&) {


}


void SceneNode::setDrawn(bool drawn) {
	this->drawn = drawn;
}


bool SceneNode::getDrawn() const {
	return this->drawn;
}


void SceneNode::setParent(SceneNode* parent) {
	this->parent = parent;
}


SceneNode& SceneNode::getParent() {
	return *this->parent;
}


void SceneNode::draw(sf::RenderWindow& window, sf::RenderStates states) const {

	//Combine transforms

	if (this->getDrawn()) {
		this->drawSelf(window, states);

		for (auto& child : children) {
			child->draw(window, states);	
		}
	}
}

void SceneNode::update(const float delta) {
	this->updateSelf(delta);

	for (auto& child : children) {
		child->update(delta);
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


bool SceneNode::operator==(const SceneNode& rhs) const {
	const SceneNode* ptr = &rhs;
	return this == ptr;
}


bool SceneNode::operator!=(const SceneNode& rhs) const {
	const SceneNode* ptr = &rhs;
	return this != ptr;
}
