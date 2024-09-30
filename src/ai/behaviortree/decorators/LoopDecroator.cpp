#include "ai/behaviortree/decorators/LoopDecorator.h"

using namespace TIE;

LoopDecorator::LoopDecorator(TIEntity& tientity) : NodeDecorator(tientity) {}

BehaviorTree::NodeStatus LoopDecorator::update(const float delta) {
    return BehaviorTree::NodeStatus::RUNNING;
}