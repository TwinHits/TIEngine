#include "ai/behaviortree/decorators/PreConditionDecorator.h"

#include "managers/ScriptManager.h"

using namespace TIE;

PreConditionDecorator::PreConditionDecorator(TIEntity& tientity): NodeDecorator(tientity) {}


BehaviorTree::NodeStatus PreConditionDecorator::update(const float delta) {
    BehaviorTree::NodeStatus status = BehaviorTree::NodeStatus::SUCCESS;
    if (this->preConditionFunctionId) {
        return ScriptManager::Instance()->runFunction<BehaviorTree::NodeStatus>(this->preConditionFunctionId, this->tientity, delta);
    }
    return status;
}


void PreConditionDecorator::setPreConditonFunctionId(const GlobalId preConditionFunctionId) {
    this->preConditionFunctionId = preConditionFunctionId;
}
