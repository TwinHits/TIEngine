#include "objects/factories/ai/BehaviorTreeNodeFactory.h"

#include <sol/sol.hpp>

#include <vector>

#include "componentsystems/BehavesComponentSystem.h"
#include "managers/HashManager.h"
#include "managers/LogManager.h"
#include "managers/ScriptManager.h"
#include "managers/WorldManager.h"
#include "objects/GlobalId.h"
#include "objects/ScriptTableReader.h"
#include "objects/ai/behaviortree/BehaviorTreeNode.h"
#include "objects/ai/behaviortree/HasEventNode.h"
#include "objects/ai/behaviortree/LeafNode.h"
#include "objects/ai/behaviortree/SelectorNode.h"
#include "objects/ai/behaviortree/SequenceNode.h"
#include "templates/MakeUnique.h"

using namespace TIE;

BehaviorTreeNodeFactory::BehaviorTreeNodeFactory(const sol::table& definition) : reader(definition) {
    this->id = HashManager::Instance()->getNewGlobalId();
    WorldManager::Instance()->saveBehaviorTreeNodeFactory(this->id, *this);
}


std::unique_ptr<BehaviorTreeNode> BehaviorTreeNodeFactory::build(TIEntity& tientity) {

    if (this->reader.hasKey(BehaviorTreeNodeFactory::NODE_TYPE)) {
        const std::string* node_type_ptr = this->reader.get<std::string>(BehaviorTreeNodeFactory::NODE_TYPE);
        if (node_type_ptr) {
            const std::string& node_type = *node_type_ptr;

            std::unique_ptr<BehaviorTreeNode> behaviorTreeNode;
            if (node_type == BehaviorTreeNodeFactory::LEAF_NODE) {
                std::unique_ptr<LeafNode> leafNode = make_unique<LeafNode>(tientity);
                leafNode->setUpdateFunctionId(*this->reader.get<GlobalId>(BehaviorTreeNodeFactory::ON_UPDATE));
                behaviorTreeNode = std::move(leafNode);

            } else if (node_type == BehaviorTreeNodeFactory::SELECTOR_NODE) {
                std::unique_ptr<SelectorNode> selectorNode = make_unique<SelectorNode>(tientity);
                std::vector<GlobalId> children;
                this->reader.get<std::vector<GlobalId>>(BehaviorTreeNodeFactory::CHILDREN, children);
                for (auto child : children) {
                    BehaviorTreeNodeFactory* childFactory = WorldManager::Instance()->getBehaviorTreeNodeFactory(child);
                    selectorNode->addChild(childFactory->build(tientity));
                }
                behaviorTreeNode = std::move(selectorNode);

            } else if (node_type == BehaviorTreeNodeFactory::SEQUENCE_NODE) {
                std::unique_ptr<SequenceNode> sequenceNode = make_unique<SequenceNode>(tientity);
                std::vector<GlobalId> children;
                this->reader.get<std::vector<GlobalId>>(BehaviorTreeNodeFactory::CHILDREN, children);
                for (auto child : children) {
                    BehaviorTreeNodeFactory* childFactory = WorldManager::Instance()->getBehaviorTreeNodeFactory(child);
                    sequenceNode->addChild(childFactory->build(tientity));
                }
                behaviorTreeNode = std::move(sequenceNode);

            } else if (node_type == BehaviorTreeNodeFactory::HAS_EVENT_NODE) {
                std::unique_ptr<HasEventNode> hasEventNode = make_unique<HasEventNode>(tientity);
                GlobalId subscription = this->reader.get<float>(BehaviorTreeNodeFactory::SUBSCRIPTION, 0);
                BehavesComponentSystem::Instance()->addSubscription(tientity, subscription, *hasEventNode);
                behaviorTreeNode = std::move(hasEventNode);

            } else {
                LogManager::Instance()->error(node_type + " is an unknown behavior tree node type.");
            }

            behaviorTreeNode->setPreConditonFunctionId(this->reader.get<GlobalId>(BehaviorTreeNodeFactory::PRE_CONDITION, 0));
            behaviorTreeNode->setPostConditonFunctionId(this->reader.get<GlobalId>(BehaviorTreeNodeFactory::POST_CONDITION, 0));

            return behaviorTreeNode;
        } else {
            LogManager::Instance()->error(tientity.getName() + " is missing a Node Type.");
        }
    } else {
        LogManager::Instance()->error(tientity.getName() + " is missing a Node Type.");
    }
    return nullptr;
}


GlobalId BehaviorTreeNodeFactory::getId() {
return this->id;
}
