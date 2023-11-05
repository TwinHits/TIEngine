#include "objects/ai/behaviortree/decorators/OnEventDecorator.h"

#include "managers/ScriptManager.h"
#include "objects/GlobalId.h"
#include "objects/ai/behaviortree/decorators/NodeDecorator.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

OnEventDecorator::OnEventDecorator(TIEntity& tientity) : NodeDecorator(tientity) {}


BehaviorTree::NodeStatus OnEventDecorator::update(const float delta) {
    BehaviorTree::NodeStatus result = BehaviorTree::NodeStatus::FAILURE;
    if (!this->messages.empty()) {
        // If any of the messages result in a success, then success
        if (this->onMessageFunctionId) {
            for (auto& message : messages) {
                BehaviorTree::NodeStatus callbackResult = ScriptManager::Instance()->runFunction<BehaviorTree::NodeStatus>(this->onMessageFunctionId, this->tientity, message);
                if (callbackResult == BehaviorTree::NodeStatus::SUCCESS) {
                    result = BehaviorTree::NodeStatus::SUCCESS;
                }
            }
        } else {
            result = BehaviorTree::NodeStatus::SUCCESS;
        }
        this->messages.clear();
    }
    return result;
}


void OnEventDecorator::setOnMessageFunctionId(const GlobalId onUpdateFunctionId) {
    this->onMessageFunctionId = onUpdateFunctionId;
}


void OnEventDecorator::onMessage(const Message& message) {
    this->messages.push_back(message);
}