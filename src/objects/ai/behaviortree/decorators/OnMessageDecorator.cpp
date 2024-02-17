#include "objects/ai/behaviortree/decorators/OnMessageDecorator.h"

#include "managers/ScriptManager.h"
#include "objects/GlobalId.h"
#include "objects/ai/behaviortree/decorators/NodeDecorator.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

OnMessageDecorator::OnMessageDecorator(TIEntity& tientity) : NodeDecorator(tientity) {}


BehaviorTree::NodeStatus OnMessageDecorator::update(const float delta) {
    BehaviorTree::NodeStatus result = this->onMessageResult;
    this->onMessageResult = BehaviorTree::NodeStatus::FAILURE;
    return result;
}


void OnMessageDecorator::setOnMessageFunctionId(const GlobalId onUpdateFunctionId) {
    this->onMessageFunctionId = onUpdateFunctionId;
}


void OnMessageDecorator::onMessage(Message& message) {
   if (this->onMessageFunctionId) {
        BehaviorTree::NodeStatus result = ScriptManager::Instance()->runFunction<BehaviorTree::NodeStatus>(this->onMessageFunctionId, this->tientity, message);
        if (result == BehaviorTree::NodeStatus::SUCCESS) {
            this->onMessageResult = result;
        }
    }
}