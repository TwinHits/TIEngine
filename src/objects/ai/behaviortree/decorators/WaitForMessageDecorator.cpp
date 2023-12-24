#include "objects/ai/behaviortree/decorators/WaitForMessageDecorator.h"

#include "managers/ScriptManager.h"
#include "objects/GlobalId.h"
#include "objects/ai/behaviortree/decorators/NodeDecorator.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

WaitForMessageDecorator::WaitForMessageDecorator(TIEntity& tientity) : NodeDecorator(tientity) {}


BehaviorTree::NodeStatus WaitForMessageDecorator::update(const float delta) {
    BehaviorTree::NodeStatus result = BehaviorTree::NodeStatus::RUNNING;
    if (!this->messages.empty()) {
        // If any of the messages result in a success, then success
        if (this->onMessageFunctionId) {
            for (auto& message : messages) {
                BehaviorTree::NodeStatus callbackResult = ScriptManager::Instance()->runFunction<BehaviorTree::NodeStatus>(this->onMessageFunctionId, this->tientity, message);
                if (callbackResult == BehaviorTree::NodeStatus::SUCCESS) {
                    result = BehaviorTree::NodeStatus::SUCCESS;
                } else if (callbackResult == BehaviorTree::NodeStatus::RUNNING) {
                    result = BehaviorTree::NodeStatus::RUNNING;
                    break;
                }
            }
        } else {
            result = BehaviorTree::NodeStatus::SUCCESS;
        }
        this->messages.clear();
    }
    return result;
}


void WaitForMessageDecorator::setOnMessageFunctionId(const GlobalId onUpdateFunctionId) {
    this->onMessageFunctionId = onUpdateFunctionId;
}


void WaitForMessageDecorator::onMessage(Message& message) {
    this->messages.push_back(message);
}