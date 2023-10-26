#include "objects/factories/ai/BehaviorTreeNodeFactory.h"

#include <sol/sol.hpp>

#include <vector>

#include "managers/HashManager.h"
#include "managers/LogManager.h"
#include "managers/ScriptManager.h"
#include "managers/WorldManager.h"
#include "objects/GlobalId.h"
#include "objects/ScriptTableReader.h"
#include "objects/ai/behaviortree/BehaviorTreeNode.h"
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

            if (node_type == BehaviorTreeNodeFactory::LEAF_NODE) {
                std::unique_ptr<LeafNode> leafNode = make_unique<LeafNode>(tientity);
                leafNode->setUpdateFunctionId(*this->reader.get<GlobalId>(BehaviorTreeNodeFactory::ON_UPDATE));
                return leafNode;

            } else if (node_type == BehaviorTreeNodeFactory::SELECTOR_NODE) {
                std::unique_ptr<SelectorNode> selectorNode = make_unique<SelectorNode>(tientity);
                std::vector<GlobalId> children;
                this->reader.get<std::vector<GlobalId>>(BehaviorTreeNodeFactory::CHILDREN, children);
                for (auto child : children) {
                    BehaviorTreeNodeFactory* childFactory = WorldManager::Instance()->getBehaviorTreeNodeFactory(child);
                    selectorNode->addChild(childFactory->build(tientity));
                }
                return selectorNode;

            } else if (node_type == BehaviorTreeNodeFactory::SEQUENCE_NODE) {
                std::unique_ptr<SequenceNode> sequenceNode = make_unique<SequenceNode>(tientity);
                std::vector<GlobalId> children;
                this->reader.get<std::vector<GlobalId>>(BehaviorTreeNodeFactory::CHILDREN, children);
                for (auto child : children) {
                    BehaviorTreeNodeFactory* childFactory = WorldManager::Instance()->getBehaviorTreeNodeFactory(child);
                    sequenceNode->addChild(childFactory->build(tientity));
                }
                return sequenceNode;
            } else {
                LogManager::Instance()->error(node_type + " is an unknown behavior tree node type.");
            }

        }
    }
}


GlobalId BehaviorTreeNodeFactory::getId() {
    return this->id;
}
