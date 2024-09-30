#include "ai/behaviortree/nodes/ParallelNode.h"

using namespace TIE;

ParallelNode::ParallelNode(TIEntity& tientity, const std::string& name) : BehaviorTreeNode(tientity, name) {
    this->nodeType = "ParallelNode";
}


BehaviorTree::NodeStatus ParallelNode::update(float delta) {
    BehaviorTree::NodeStatus result = this->updatePreDecorators(delta);
    if (result == BehaviorTree::NodeStatus::SUCCESS) {
        // Iterate through all children
        // Should it return sucess if one succeeds, or return failure if one fails?
        for (auto& child : this->children) {
            BehaviorTree::NodeStatus nodeResult = child->update(delta);
            if (nodeResult == BehaviorTree::NodeStatus::FAILURE) {
                result = nodeResult;
            }
        }
        if (result == BehaviorTree::NodeStatus::SUCCESS) {
            result = this->updatePostDecorators(delta);
        }
    }
    BehaviorTreeNode::publishNodeStatusEvent(result);
    return result;
}