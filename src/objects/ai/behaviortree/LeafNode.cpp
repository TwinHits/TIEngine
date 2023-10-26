#include "objects/ai/behaviortree/LeafNode.h"

#include "managers/ScriptManager.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

LeafNode::LeafNode(TIEntity& tientity) : BehaviorTreeNode(tientity) {}


BehaviorTree::NodeStatus LeafNode::update(float delta) {
    return this->runFunction(this->getUpdateFunctionId(), delta);
}


const GlobalId LeafNode::getUpdateFunctionId() {
    return this->updateFunctionId;
}


void LeafNode::setUpdateFunctionId(const GlobalId updateFunctionId) {
    this->updateFunctionId = updateFunctionId;
}


BehaviorTree::NodeStatus LeafNode::runFunction(const GlobalId functionId, const float delta) {
    return ScriptManager::Instance()->runFunction<BehaviorTree::NodeStatus>(functionId, this->tientity, delta);
}

