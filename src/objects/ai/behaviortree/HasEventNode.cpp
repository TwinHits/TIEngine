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
    return BehaviorTree::NodeStatus::SUCCESS;
}


BehaviorTree::NodeStatus HasEventNode::update(float delta) {
    BehaviorTree::NodeStatus result = BehaviorTree::NodeStatus::FAILURE;
    if (!messages.empty()) {
        for (auto& message : this->messages) {
            result = this->preCondition(message);
            if (result == BehaviorTree::SUCCESS) {
                break;
            }
        }
        result = this->postCondition(result);
        this->messages.clear();
    }
    return result;
}


void HasEventNode::onMessage(const Message& message) {
    this->messages.push_back(message);
}