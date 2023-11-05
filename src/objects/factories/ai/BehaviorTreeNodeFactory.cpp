#include "objects/factories/ai/BehaviorTreeNodeFactory.h"

#include <sol/sol.hpp>

#include <vector>

#include "componentsystems/BehavesComponentSystem.h"
#include "componentsystems/MessagesComponentSystem.h"
#include "managers/HashManager.h"
#include "managers/LogManager.h"
#include "managers/ScriptManager.h"
#include "managers/WorldManager.h"
#include "objects/GlobalId.h"
#include "objects/Message.h"
#include "objects/ScriptTableReader.h"
#include "objects/ai/behaviortree/decorators/OnEventDecorator.h"
#include "objects/ai/behaviortree/decorators/PreConditionDecorator.h"
#include "objects/ai/behaviortree/decorators/PostConditionDecorator.h"
#include "objects/ai/behaviortree/decorators/WaitForEventDecorator.h"
#include "objects/ai/behaviortree/nodes/BehaviorTreeNode.h"
#include "objects/ai/behaviortree/nodes/LeafNode.h"
#include "objects/ai/behaviortree/nodes/ParallelNode.h"
#include "objects/ai/behaviortree/nodes/SelectorNode.h"
#include "objects/ai/behaviortree/nodes/SequenceNode.h"
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
                behaviorTreeNode = this->buildLeafNode(tientity);
            } else if (node_type == BehaviorTreeNodeFactory::SELECTOR_NODE) {
                behaviorTreeNode = this->buildSelectorNode(tientity);
            } else if (node_type == BehaviorTreeNodeFactory::SEQUENCE_NODE) {
                behaviorTreeNode = this->buildSequenceNode(tientity);
            } else if (node_type == BehaviorTreeNodeFactory::PARALLEL_NODE) {
                behaviorTreeNode = this->buildParallelNode(tientity);
            } else {
                LogManager::Instance()->error(node_type + " is an unknown behavior tree node type.");
                return nullptr;
            }

            if (this->reader.hasKey(BehaviorTreeNodeFactory::ON_MESSAGE)) {
                std::unique_ptr<OnEventDecorator> onEventDecorator = make_unique<OnEventDecorator>(tientity);
                onEventDecorator->setOnMessageFunctionId(this->reader.get<GlobalId>(BehaviorTreeNodeFactory::ON_MESSAGE, 0));
                std::vector<GlobalId> subscriptions;
                this->reader.get<std::vector<GlobalId>>(BehaviorTreeNodeFactory::SUBSCRIPTIONS, subscriptions);
                for (auto subscription : subscriptions) {
                    MessagesComponentSystem::Instance()->subscribe(tientity, subscription, std::bind(&OnEventDecorator::onMessage, onEventDecorator.get(), std::placeholders::_1));
                }
                behaviorTreeNode->addPreDecorator(std::move(onEventDecorator));
            }
            
            if (this->reader.hasKey(BehaviorTreeNodeFactory::WAIT_FOR_MESSAGE)) {
                std::unique_ptr<WaitForEventDecorator> waitForEventDecorator = make_unique<WaitForEventDecorator>(tientity);
                waitForEventDecorator->setOnMessageFunctionId(this->reader.get<GlobalId>(BehaviorTreeNodeFactory::WAIT_FOR_MESSAGE, 0));
                std::vector<GlobalId> subscriptions;
                this->reader.get<std::vector<GlobalId>>(BehaviorTreeNodeFactory::SUBSCRIPTIONS, subscriptions);
                for (auto subscription : subscriptions) {
                    MessagesComponentSystem::Instance()->subscribe(tientity, subscription, std::bind(&WaitForEventDecorator::onMessage, waitForEventDecorator.get(), std::placeholders::_1));
                }
                behaviorTreeNode->addPreDecorator(std::move(waitForEventDecorator));
            }

            if (this->reader.hasKey(BehaviorTreeNodeFactory::PRE_CONDITION)) {
                std::unique_ptr<PreConditionDecorator> preConditionDecorator = make_unique<PreConditionDecorator>(tientity);
                preConditionDecorator->setPreConditonFunctionId(this->reader.get<GlobalId>(BehaviorTreeNodeFactory::PRE_CONDITION, 0));
                behaviorTreeNode->addPreDecorator(std::move(preConditionDecorator));
            }

            if (this->reader.hasKey(BehaviorTreeNodeFactory::POST_CONDITION)) {
                std::unique_ptr<PostConditionDecorator> postConditionDecorator = make_unique<PostConditionDecorator>(tientity);
                postConditionDecorator->setPostConditonFunctionId(this->reader.get<GlobalId>(BehaviorTreeNodeFactory::POST_CONDITION, 0));
                behaviorTreeNode->addPostDecorator(std::move(postConditionDecorator));
            }

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


std::unique_ptr<BehaviorTreeNode> BehaviorTreeNodeFactory::buildLeafNode(TIEntity& tientity) {
    std::unique_ptr<LeafNode> leafNode = make_unique<LeafNode>(tientity);
    leafNode->setUpdateFunctionId(this->reader.get<GlobalId>(BehaviorTreeNodeFactory::ON_UPDATE, 0));
    return std::move(leafNode);
}


std::unique_ptr<BehaviorTreeNode> BehaviorTreeNodeFactory::buildSelectorNode(TIEntity& tientity) {
    std::unique_ptr<SelectorNode> selectorNode = make_unique<SelectorNode>(tientity);
    std::vector<GlobalId> children;
    this->reader.get<std::vector<GlobalId>>(BehaviorTreeNodeFactory::CHILDREN, children);
    for (auto child : children) {
        BehaviorTreeNodeFactory* childFactory = WorldManager::Instance()->getBehaviorTreeNodeFactory(child);
        selectorNode->addChild(childFactory->build(tientity));
    }
   return std::move(selectorNode);
}


std::unique_ptr<BehaviorTreeNode> BehaviorTreeNodeFactory::buildSequenceNode(TIEntity& tientity) {
    std::unique_ptr<SequenceNode> sequenceNode = make_unique<SequenceNode>(tientity);
    std::vector<GlobalId> children;
    this->reader.get<std::vector<GlobalId>>(BehaviorTreeNodeFactory::CHILDREN, children);
    for (auto child : children) {
        BehaviorTreeNodeFactory* childFactory = WorldManager::Instance()->getBehaviorTreeNodeFactory(child);
        sequenceNode->addChild(childFactory->build(tientity));
    }
    return std::move(sequenceNode);
}


std::unique_ptr<BehaviorTreeNode> BehaviorTreeNodeFactory::buildParallelNode(TIEntity& tientity) {
    std::unique_ptr<ParallelNode> parallelNode = make_unique<ParallelNode>(tientity);
    std::vector<GlobalId> children;
    this->reader.get<std::vector<GlobalId>>(BehaviorTreeNodeFactory::CHILDREN, children);
    for (auto child : children) {
        BehaviorTreeNodeFactory* childFactory = WorldManager::Instance()->getBehaviorTreeNodeFactory(child);
        parallelNode->addChild(childFactory->build(tientity));
    }
    return std::move(parallelNode);
}
