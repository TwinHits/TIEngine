#include "objects/ai/behaviortree/nodes/HasEventNode.h"

#include "managers/ScriptManager.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

HasEventNode::HasEventNode(TIEntity& tientity) : BehaviorTreeNode(tientity) {}


BehaviorTree::NodeStatus HasEventNode::update(float delta) {
    BehaviorTree::NodeStatus result = BehaviorTree::NodeStatus::FAILURE;
    if (!messages.empty()) {
        for (auto& message : this->messages) {
            result = this->updatePreDecorators(delta);
            if (result == BehaviorTree::NodeStatus::SUCCESS) {
                result = this->updatePostDecorators(delta);
            }
        }
        this->messages.clear();
    }
    return result;
}


void HasEventNode::onMessage(const Message& message) {
    this->messages.push_back(message);
}