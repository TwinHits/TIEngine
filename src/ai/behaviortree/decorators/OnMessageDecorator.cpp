#include "ai/behaviortree/decorators/OnMessageDecorator.h"

#include "memory"

#include "managers/ScriptManager.h"
#include "objects/GlobalId.h"
#include "ai/behaviortree/decorators/NodeDecorator.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

OnMessageDecorator::OnMessageDecorator(TIEntity& tientity) : NodeDecorator(tientity) {}

BehaviorTree::NodeStatus OnMessageDecorator::update(const float delta) {
    BehaviorTree::NodeStatus result = BehaviorTree::NodeStatus::FAILURE;
    if (!this->message.expired() && this->onMessageFunctionId) {
        std::shared_ptr message = this->message.lock();
        result = ScriptManager::Instance()->runFunction<BehaviorTree::NodeStatus>(this->onMessageFunctionId, this->tientity, *message);
    }
    return result;
}


void OnMessageDecorator::setOnMessageFunctionId(const GlobalId onUpdateFunctionId) {
    this->onMessageFunctionId = onUpdateFunctionId;
}


void OnMessageDecorator::onMessage(std::shared_ptr<Message> message) {
    this->message = std::weak_ptr<Message>(message);
}