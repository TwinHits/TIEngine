#include "objects/ai/behaviortree/BehaviorTreeNode.h"

#include "objects/Message.h"
#include "objects/tientities/TIEntity.h"
#include "managers/ScriptManager.h"

using namespace TIE;


BehaviorTreeNode::BehaviorTreeNode(TIEntity& tientity) : tientity(tientity) {}


BehaviorTree::NodeStatus BehaviorTreeNode::preCondition() {
    if (this->preConditionFunctionId) {
        return ScriptManager::Instance()->runFunction<BehaviorTree::NodeStatus>(this->preConditionFunctionId, this->tientity);
    }
    return BehaviorTree::NodeStatus::SUCCESS;
}


BehaviorTree::NodeStatus BehaviorTreeNode::postCondition() {
    if (this->postConditionFunctionId) {
        return ScriptManager::Instance()->runFunction<BehaviorTree::NodeStatus>(this->postConditionFunctionId, this->tientity);
    }
    return BehaviorTree::NodeStatus::SUCCESS;
}


void BehaviorTreeNode::setPreConditonFunctionId(const GlobalId preConditionFunctionId) {
    this->preConditionFunctionId = preConditionFunctionId;
}


void BehaviorTreeNode::setPostConditonFunctionId(const GlobalId postConditionFunctionId) {
    this->postConditionFunctionId = postConditionFunctionId;
}


void BehaviorTreeNode::setOnMessageFunctionId(const GlobalId onMessageFunctionId) {
    this->onMessageFunctionId = onMessageFunctionId;
}


void BehaviorTreeNode::addChild(std::unique_ptr<BehaviorTreeNode> behaviorTreeNode) {
    this->children.push_back(std::move(behaviorTreeNode));
}


void BehaviorTreeNode::onMessage(const Message& message) {
    if (this->onMessageFunctionId) {
        ScriptManager::Instance()->runFunction<sol::optional<float>>(this->onMessageFunctionId, this->tientity, message);
    }
}