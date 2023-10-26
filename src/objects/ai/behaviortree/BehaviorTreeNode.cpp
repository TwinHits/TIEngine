#include "objects/ai/behaviortree/BehaviorTreeNode.h"

#include "objects/tientities/TIEntity.h"

using namespace TIE;


BehaviorTreeNode::BehaviorTreeNode(TIEntity& tientity) : tientity(tientity) {}


void BehaviorTreeNode::addChild(std::unique_ptr<BehaviorTreeNode> behaviorTreeNode) {
    this->children.push_back(std::move(behaviorTreeNode));
}
