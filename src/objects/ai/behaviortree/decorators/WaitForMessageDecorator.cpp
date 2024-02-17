#include "objects/ai/behaviortree/decorators/WaitForMessageDecorator.h"

#include "managers/ScriptManager.h"
#include "objects/GlobalId.h"
#include "objects/ai/behaviortree/decorators/NodeDecorator.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

WaitForMessageDecorator::WaitForMessageDecorator(TIEntity& tientity) : NodeDecorator(tientity) {}


BehaviorTree::NodeStatus WaitForMessageDecorator::update(const float delta) {
    BehaviorTree::NodeStatus result = this->onMessageResult;
    this->onMessageResult = BehaviorTree::NodeStatus::RUNNING;
    return result;
}


void WaitForMessageDecorator::setOnMessageFunctionId(const GlobalId onUpdateFunctionId) {
    this->onMessageFunctionId = onUpdateFunctionId;
}


void WaitForMessageDecorator::onMessage(Message& message) {
    if (this->onMessageFunctionId) {
        BehaviorTree::NodeStatus result = ScriptManager::Instance()->runFunction<BehaviorTree::NodeStatus>(this->onMessageFunctionId, this->tientity, message);
        if (result == BehaviorTree::NodeStatus::SUCCESS) {
            this->onMessageResult = result;
        }
    }
}