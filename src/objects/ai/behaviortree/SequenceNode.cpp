#include "objects/ai/behaviortree/SequenceNode.h"

#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

SequenceNode::SequenceNode(TIEntity& tientity) : BehaviorTreeNode(tientity) {}


BehaviorTree::NodeStatus SequenceNode::update(float delta) {
    // Iterate through children until one does not return success. 
    // Return to that one on next run.
    BehaviorTree::NodeStatus result = BehaviorTree::NodeStatus::SUCCESS;
    for (auto& child : this->children) {
        if (this->resumeNode == nullptr || this->resumeNode == child.get()) {
            result = child->update(delta);
            if (result == BehaviorTree::NodeStatus::SUCCESS) {
                // Continue to next child
                this->resumeNode = nullptr;
            } else if (result == BehaviorTree::NodeStatus::RUNNING) {
                // Resume this child on next update
                this->resumeNode = child.get();
                break;
            } else if (result == BehaviorTree::NodeStatus::FAILURE) {
                // Restart from beginning on next update
                this->resumeNode = nullptr;
                result = BehaviorTree::RUNNING;
                break;
            }
        }
    }
    return result;
}