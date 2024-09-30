#include "ai/behaviortree/nodes/LeafNode.h"

#include <string>

#include "managers/ScriptManager.h"

using namespace TIE;

LeafNode::LeafNode(TIEntity& tientity, const std::string& name) : BehaviorTreeNode(tientity, name) {
    this->nodeType = "LeafNode";
}


BehaviorTree::NodeStatus LeafNode::update(float delta) {
    BehaviorTree::NodeStatus result = this->updatePreDecorators(delta);
    if (result == BehaviorTree::NodeStatus::SUCCESS) {
        if (this->updateFunctionId) {
            result = ScriptManager::Instance()->runFunction<BehaviorTree::NodeStatus>(this->updateFunctionId, this->tientity, delta);
        }
        if (result == BehaviorTree::NodeStatus::SUCCESS) {
            result = this->updatePostDecorators(delta);
        }
    }
    BehaviorTreeNode::publishNodeStatusEvent(result);
    return result;
}


const GlobalId LeafNode::getUpdateFunctionId() {
    return this->updateFunctionId;
}


void LeafNode::setUpdateFunctionId(const GlobalId updateFunctionId) {
    this->updateFunctionId = updateFunctionId;
}
