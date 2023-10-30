#include "objects/ai/behaviortree/WaitForEventNode.h"

#include "managers/ScriptManager.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

WaitForEventNode::WaitForEventNode(TIEntity& tientity) : BehaviorTreeNode(tientity) {}


BehaviorTree::NodeStatus WaitForEventNode::preCondition(const Message& message) {
    if (this->preConditionFunctionId) {
        return ScriptManager::Instance()->runFunction<BehaviorTree::NodeStatus>(this->preConditionFunctionId, this->tientity, message);
    }
    return BehaviorTree::NodeStatus::SUCCESS;
}


BehaviorTree::NodeStatus WaitForEventNode::update(float delta) {
    BehaviorTree::NodeStatus result = BehaviorTree::NodeStatus::RUNNING;
    if (!messages.empty()) {
        for (auto& message : this->messages) {
            result = this->preCondition(message);
            if (result == BehaviorTree::SUCCESS) {
                break;
            }
        }
        //result = this->postCondition();
        this->messages.clear();
    }
    return result;
}


void WaitForEventNode::onMessage(const Message& message) {
    this->messages.push_back(message);
}