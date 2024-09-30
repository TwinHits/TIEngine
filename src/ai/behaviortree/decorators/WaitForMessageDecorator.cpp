#include "ai/behaviortree/decorators/WaitForMessageDecorator.h"

#include "managers/ScriptManager.h"

using namespace TIE;

WaitForMessageDecorator::WaitForMessageDecorator(TIEntity& tientity) : NodeDecorator(tientity) {}


BehaviorTree::NodeStatus WaitForMessageDecorator::update(const float delta) {
    BehaviorTree::NodeStatus result = BehaviorTree::NodeStatus::RUNNING;
    if (!this->message.expired() && this->onMessageFunctionId) {
        std::shared_ptr message = this->message.lock();
        result = ScriptManager::Instance()->runFunction<BehaviorTree::NodeStatus>(this->onMessageFunctionId, this->tientity, *message);
    }
    return result;
}


void WaitForMessageDecorator::setOnMessageFunctionId(const GlobalId onUpdateFunctionId) {
    this->onMessageFunctionId = onUpdateFunctionId;
}


void WaitForMessageDecorator::onMessage(std::shared_ptr<Message> message) {
    this->message = std::weak_ptr<Message>(message);
}