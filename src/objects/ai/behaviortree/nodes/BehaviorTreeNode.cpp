#include "objects/ai/behaviortree/nodes/BehaviorTreeNode.h"

#include "managers/ScriptManager.h"
#include "objects/Message.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;


BehaviorTreeNode::BehaviorTreeNode(TIEntity& tientity) : tientity(tientity) {}


TIEntity& BehaviorTreeNode::getTIEntity() {
    return this->tientity;
}


BehaviorTree::NodeStatus BehaviorTreeNode::updatePreDecorators(float delta) {
    return this->updateDecorators(this->preDecorators, delta);
}


BehaviorTree::NodeStatus BehaviorTreeNode::updatePostDecorators(float delta) {
    return this->updateDecorators(this->postDecorators, delta);
}


void BehaviorTreeNode::setOnMessageFunctionId(const GlobalId onMessageFunctionId) {
    this->onMessageFunctionId = onMessageFunctionId;
}


void BehaviorTreeNode::addPreDecorator(std::unique_ptr<NodeDecorator> decorator) {
    this->preDecorators.push_back(std::move(decorator));
}


void BehaviorTreeNode::addChild(std::unique_ptr<BehaviorTreeNode> behaviorTreeNode) {
    this->children.push_back(std::move(behaviorTreeNode));
}


void BehaviorTreeNode::addPostDecorator(std::unique_ptr<NodeDecorator> decorator) {
    this->postDecorators.push_back(std::move(decorator));
}


void BehaviorTreeNode::onMessage(const Message& message) {
    if (this->onMessageFunctionId) {
        ScriptManager::Instance()->runFunction<sol::optional<float>>(this->onMessageFunctionId, this->tientity, message);
    }
}


BehaviorTree::NodeStatus BehaviorTreeNode::updateDecorators(const std::vector<std::unique_ptr<NodeDecorator>>& decorators, float delta) {
    BehaviorTree::NodeStatus result = BehaviorTree::NodeStatus::SUCCESS;
    for (auto& decorator : decorators) {
        result = decorator->update(delta);
        if (result == BehaviorTree::NodeStatus::FAILURE) {
            break;
        }
    }
    return result;
}
