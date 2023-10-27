#include "objects/ai/behaviortree/HasEventNode.h"

#include "managers/ScriptManager.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

HasEventNode::HasEventNode(TIEntity& tientity) : BehaviorTreeNode(tientity) {}


BehaviorTree::NodeStatus HasEventNode::preCondition(const Message& message) {
    if (this->preConditionFunctionId) {
        return ScriptManager::Instance()->runFunction<BehaviorTree::NodeStatus>(this->preConditionFunctionId, this->tientity, message);
    }
}


BehaviorTree::NodeStatus HasEventNode::update(float delta) {
    if (this->hasMessage) {
        BehaviorTree::NodeStatus result = this->preCondition(this->message);
        // result = this->postCondition();
        this->hasMessage = false;
        return result;
    }
    return BehaviorTree::NodeStatus::FAILURE;
}


void HasEventNode::onMessage(const Message& message) {
    this->hasMessage = true;
    this->message = message;
}