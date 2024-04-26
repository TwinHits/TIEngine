#include "objects/ai/behaviortree/nodes/SequenceNode.h"

#include <string>

#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

SequenceNode::SequenceNode(TIEntity& tientity, const std::string& name) : BehaviorTreeNode(tientity, name) {
    this->nodeType = "SequenceNode";
}


BehaviorTree::NodeStatus SequenceNode::update(float delta) {
    BehaviorTree::NodeStatus result = this->updatePreDecorators(delta);
    if (result == BehaviorTree::NodeStatus::SUCCESS) {
        // Iterate through children until one does not return success. 
        // Return to that one on next run.
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
        if (result == BehaviorTree::NodeStatus::SUCCESS) {
            result = this->updatePostDecorators(delta);
        }
    }
    BehaviorTreeNode::update(delta);
    return result;
}