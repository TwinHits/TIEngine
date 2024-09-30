#include "ai/behaviortree/decorators/PostConditionDecorator.h"

#include "managers/ScriptManager.h"

using namespace TIE;

PostConditionDecorator::PostConditionDecorator(TIEntity& tientity) : NodeDecorator(tientity) {}


BehaviorTree::NodeStatus PostConditionDecorator::update(const float delta) {
    BehaviorTree::NodeStatus status = BehaviorTree::NodeStatus::SUCCESS;
    if (this->postConditionFunctionId) {
        return ScriptManager::Instance()->runFunction<BehaviorTree::NodeStatus>(this->postConditionFunctionId, this->tientity, delta);
    }
    return status;
}


void PostConditionDecorator::setPostConditonFunctionId(const GlobalId postConditionFunctionId) {
    this->postConditionFunctionId = postConditionFunctionId;
}