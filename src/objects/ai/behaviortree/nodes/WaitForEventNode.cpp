#include "objects/ai/behaviortree/nodes/WaitForEventNode.h"

#include "managers/ScriptManager.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

WaitForEventNode::WaitForEventNode(TIEntity& tientity) : BehaviorTreeNode(tientity) {}


BehaviorTree::NodeStatus WaitForEventNode::update(float delta) {
    BehaviorTree::NodeStatus result = BehaviorTree::NodeStatus::RUNNING;
    if (!messages.empty()) {
        for (auto& message : this->messages) {
            result = this->updatePreDecorators(delta);
            if (result == BehaviorTree::SUCCESS) {
                result = this->updatePostDecorators(delta);
                break;
            }
        }
        this->messages.clear();
    }
    return result;
}


void WaitForEventNode::onMessage(const Message& message) {
    this->messages.push_back(message);
}