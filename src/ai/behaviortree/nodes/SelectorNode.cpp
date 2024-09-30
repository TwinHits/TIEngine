#include "ai/behaviortree/nodes/SelectorNode.h"

using namespace TIE;

SelectorNode::SelectorNode(TIEntity& tientity, const std::string& name) : BehaviorTreeNode(tientity, name) {
    this->nodeType = "SelectorNode";
}


BehaviorTree::NodeStatus SelectorNode::update(float delta) {
    BehaviorTree::NodeStatus result = this->updatePreDecorators(delta);
    if (result == BehaviorTree::NodeStatus::SUCCESS) {
        // Iterate through children until one returns a success
        // If one returns running, return running and continue that one on next frame
        for (auto& child : this->children) {
            if (this->resumeNode == nullptr || this->resumeNode == child.get()) {
                result = child->update(delta);
                if (result == BehaviorTree::NodeStatus::SUCCESS) {
                    // Restart from beginning on next update
                    this->resumeNode = nullptr;
                    break;
                } else if (result == BehaviorTree::NodeStatus::RUNNING) {
                    // Resume this child on next update
                    this->resumeNode = child.get();
                    break;
                } else if (result == BehaviorTree::NodeStatus::FAILURE) {
                    // Continue to next child
                    this->resumeNode = nullptr;
                    continue;
                }
            }
        }
        if (result == BehaviorTree::NodeStatus::SUCCESS) {
            result = this->updatePostDecorators(delta);
        }
    }
    BehaviorTreeNode::publishNodeStatusEvent(result);
    return result;
}
