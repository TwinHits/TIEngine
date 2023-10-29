#include "objects/ai/behaviortree/ParallelNode.h"

#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

ParallelNode::ParallelNode(TIEntity& tientity) : BehaviorTreeNode(tientity) {}


BehaviorTree::NodeStatus ParallelNode::update(float delta) {
    BehaviorTree::NodeStatus result = this->preCondition();
    if (result == BehaviorTree::NodeStatus::SUCCESS) {
        // Iterate through all children
        // Should it return sucess if one succeeds, or return failure if one fails?
        for (auto& child : this->children) {
            BehaviorTree::NodeStatus nodeResult = child->update(delta);
            if (nodeResult == BehaviorTree::NodeStatus::FAILURE) {
                result = nodeResult;
            }
        }
    }
    // result = this->postCondition(result);
    return result;
}