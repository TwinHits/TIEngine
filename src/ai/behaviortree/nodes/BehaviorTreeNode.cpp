#include "ai/behaviortree/nodes/BehaviorTreeNode.h"

#include <string>

#include "componentsystems/BehavesComponentSystem.h"
#include "componentsystems/EventsComponentSystem.h"
#include "enumeration/NodeStatus.h"
#include "managers/HashManager.h"
#include "objects/Message.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;


BehaviorTreeNode::BehaviorTreeNode(TIEntity& tientity, const std::string& name) : tientity(tientity) {
    this->id = HashManager::Instance()->getNewGlobalId();
    this->name = name;
    this->nodeType = "BehaviorTreeNode";
}


const GlobalId BehaviorTreeNode::getId() {
    return this->id;
}


TIEntity& BehaviorTreeNode::getTIEntity() {
    return this->tientity;
}


const std::string& BehaviorTreeNode::getName() {
    return this->name;
}


const std::string& BehaviorTreeNode::getNodeType() {
    return this->nodeType;
}


BehaviorTree::NodeStatus BehaviorTreeNode::updatePreDecorators(float delta) {
    return this->updateDecorators(this->preDecorators, delta);
}


BehaviorTree::NodeStatus BehaviorTreeNode::updatePostDecorators(float delta) {
    return this->updateDecorators(this->postDecorators, delta);
}


void BehaviorTreeNode::addPreDecorator(std::unique_ptr<NodeDecorator> decorator) {
    this->preDecorators.push_back(std::move(decorator));
}


void BehaviorTreeNode::addChild(std::unique_ptr<BehaviorTreeNode> behaviorTreeNode) {
    this->children.push_back(std::move(behaviorTreeNode));
}


const std::vector<std::unique_ptr<BehaviorTreeNode>>& BehaviorTreeNode::getChildren() {
    return this->children;
}


void BehaviorTreeNode::addPostDecorator(std::unique_ptr<NodeDecorator> decorator) {
    this->postDecorators.push_back(std::move(decorator));
}


BehaviorTree::NodeStatus BehaviorTreeNode::updateDecorators(const std::vector<std::unique_ptr<NodeDecorator>>& decorators, float delta) {
    BehaviorTree::NodeStatus result = BehaviorTree::NodeStatus::SUCCESS;
    for (auto& decorator : decorators) {
        if (this->resumeDecorator == nullptr || this->resumeDecorator == decorator.get()) {
            this->resumeDecorator = nullptr;
            result = decorator->update(delta);
            if (result == BehaviorTree::NodeStatus::FAILURE) {
                break;
            } else if (result == BehaviorTree::NodeStatus::RUNNING) {
                this->resumeDecorator = decorator.get();
                break;
            }
        }
    }
    return result;
}


void BehaviorTreeNode::publishNodeStatusEvent(BehaviorTree::NodeStatus nodeStatus) {
    EventsComponentSystem::Instance()->publish(Message(BehavesComponentSystem::Instance()->getMessageSubscriptionForNodeStatus(nodeStatus), this->id));
}
