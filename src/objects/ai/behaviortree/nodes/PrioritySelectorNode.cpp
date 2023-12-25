#include "objects/ai/behaviortree/nodes/PrioritySelectorNode.h"

#include <string>

#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

PrioritySelectorNode::PrioritySelectorNode(TIEntity& tientity, const std::string& name) : BehaviorTreeNode(tientity, name) {}


BehaviorTree::NodeStatus PrioritySelectorNode::update(float delta) {
    BehaviorTree::NodeStatus result = this->updatePreDecorators(delta);
    if (result == BehaviorTree::NodeStatus::SUCCESS) {
        // Iterate through children until one returns running or success.
        // Always start witht he first child in case conditions change since it has higher priority
        for (auto& child : this->children) {
            result = child->update(delta);
            if (result == BehaviorTree::NodeStatus::SUCCESS) {
                // Restart from beginning on next update
                break;
            } else if (result == BehaviorTree::NodeStatus::RUNNING) {
                // Restart from beginning on next update
                break;
            } else if (result == BehaviorTree::NodeStatus::FAILURE) {
                // Continue to next child
                continue;
            }
        }
        if (result == BehaviorTree::NodeStatus::SUCCESS) {
            result = this->updatePostDecorators(delta);
        }
    }
    return result;
}
