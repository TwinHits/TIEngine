#include "objects/ai/behaviortree/HasEventNode.h"

#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

HasEventNode::HasEventNode(TIEntity& tientity) : BehaviorTreeNode(tientity) {}


BehaviorTree::NodeStatus HasEventNode::update(float delta) {
    if (hasMessage) {
        this->hasMessage = false;
        return BehaviorTree::NodeStatus::SUCCESS;
    } else {
        return BehaviorTree::NodeStatus::FAILURE;
    }
}


void HasEventNode::onMessage(const Message& message) {
    this->hasMessage = true;
}