#include "objects/ai/behaviortree/nodes/LeafNode.h"

#include "managers/ScriptManager.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

LeafNode::LeafNode(TIEntity& tientity) : BehaviorTreeNode(tientity) {}


BehaviorTree::NodeStatus LeafNode::update(float delta) {
    BehaviorTree::NodeStatus result = this->updatePreDecorators(delta);
    if (result == BehaviorTree::NodeStatus::SUCCESS) {
        if (this->updateFunctionId) {
            result = ScriptManager::Instance()->runFunction<BehaviorTree::NodeStatus>(this->updateFunctionId, this->tientity, delta);
        }
        if (result == BehaviorTree::NodeStatus::SUCCESS) {
            result = this->updatePostDecorators(delta);
        }
    }
    return result;
}


const GlobalId LeafNode::getUpdateFunctionId() {
    return this->updateFunctionId;
}


void LeafNode::setUpdateFunctionId(const GlobalId updateFunctionId) {
    this->updateFunctionId = updateFunctionId;
}
