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
#include "ai/behaviortree/decorators/LoopDecorator.h"
#include "ai/behaviortree/decorators/OnMessageDecorator.h"
#include "ai/behaviortree/decorators/PreConditionDecorator.h"
#include "ai/behaviortree/decorators/PostConditionDecorator.h"
#include "ai/behaviortree/decorators/WaitForMessageDecorator.h"
#include "ai/behaviortree/nodes/BehaviorTreeNode.h"
#include "ai/behaviortree/nodes/LeafNode.h"
#include "ai/behaviortree/nodes/ParallelNode.h"
#include "ai/behaviortree/nodes/PrioritySelectorNode.h"
#include "ai/behaviortree/nodes/SelectorNode.h"
#include "ai/behaviortree/nodes/SequenceNode.h"
#include "templates/MakeUnique.h"

using namespace TIE;

BehaviorTreeNodeFactory::BehaviorTreeNodeFactory(const sol::table& definition) : reader(definition) {
    this->id = HashManager::Instance()->getNewGlobalId();
    WorldManager::Instance()->saveBehaviorTreeNodeFactory(this->id, *this);
}


std::unique_ptr<BehaviorTreeNode> BehaviorTreeNodeFactory::build(TIEntity& tientity) {

    if (this->reader.hasKey(BehaviorTreeNodeFactory::NODE_TYPE)) {
        const std::string& nodeType = this->reader.get<std::string>(BehaviorTreeNodeFactory::NODE_TYPE, "");
        const std::string& name = this->reader.get<std::string>(BehaviorTreeNodeFactory::NAME, "");

        std::unique_ptr<BehaviorTreeNode> behaviorTreeNode;
        if (nodeType == BehaviorTreeNodeFactory::LEAF_NODE) {
            behaviorTreeNode = this->buildLeafNode(tientity);
        } else if (nodeType == BehaviorTreeNodeFactory::PARALLEL_NODE) {
            behaviorTreeNode = this->buildParallelNode(tientity);
        } else if (nodeType == BehaviorTreeNodeFactory::PRIORITY_SELECTOR_NODE) {
            behaviorTreeNode = this->buildPrioritySelectorNode(tientity);
        } else if (nodeType == BehaviorTreeNodeFactory::SELECTOR_NODE) {
            behaviorTreeNode = this->buildSelectorNode(tientity);
        } else if (nodeType == BehaviorTreeNodeFactory::SEQUENCE_NODE) {
            behaviorTreeNode = this->buildSequenceNode(tientity);
        } else {
            LogManager::Instance()->error(nodeType + " is an unknown behavior tree node type.");
            return nullptr;
        }

        if (this->reader.hasKey(BehaviorTreeNodeFactory::DECORATORS)) {
            const ScriptTableReader& decorators = this->reader.getReader(BehaviorTreeNodeFactory::DECORATORS);
            for (auto& [index, decoratorReader] : decorators.getReaders()) {

                const std::string& decoratorType = decoratorReader.get<std::string>(BehaviorTreeNodeFactory::DECORATOR_TYPE, "");
                if (decoratorType == BehaviorTreeNodeFactory::PRE_CONDITION) {
                    this->addPreConditionDecorator(tientity, decoratorReader, *behaviorTreeNode);
                } else if (decoratorType == BehaviorTreeNodeFactory::POST_CONDITION) {
                    this->addPostConditionDecorator(tientity, decoratorReader, *behaviorTreeNode);
                } else if (decoratorType == BehaviorTreeNodeFactory::ON_MESSAGE) {
                    this->addOnMessageDecorator(tientity, decoratorReader, *behaviorTreeNode);
                } else if (decoratorType == BehaviorTreeNodeFactory::WAIT_FOR_MESSAGE) {
                    this->addWaitForMessageDecorator(tientity, decoratorReader, *behaviorTreeNode);
                } else if (decoratorType == BehaviorTreeNodeFactory::LOOP) {
                    this->addLoopDecorator(tientity, decoratorReader, *behaviorTreeNode);
                } else {
                    LogManager::Instance()->error(decoratorType + " is an unknown decorator type.");
                }
            }
        }

        return behaviorTreeNode;
    } else {
        LogManager::Instance()->error(tientity.getName() + " is missing a Node Type.");
    }
    return nullptr;
}


GlobalId BehaviorTreeNodeFactory::getId() {
    return this->id;
}


std::unique_ptr<BehaviorTreeNode> BehaviorTreeNodeFactory::buildLeafNode(TIEntity& tientity) {
    const std::string& name = this->reader.get<std::string>(BehaviorTreeNodeFactory::NAME, "");
    std::unique_ptr<LeafNode> leafNode = std::make_unique<LeafNode>(tientity, name);
    leafNode->setUpdateFunctionId(this->reader.get<GlobalId>(BehaviorTreeNodeFactory::ON_UPDATE, 0));
    return std::move(leafNode);
}


std::unique_ptr<BehaviorTreeNode> BehaviorTreeNodeFactory::buildParallelNode(TIEntity& tientity) {
    const std::string& name = this->reader.get<std::string>(BehaviorTreeNodeFactory::NAME, "");
    std::unique_ptr<ParallelNode> parallelNode = std::make_unique<ParallelNode>(tientity, name);
    std::vector<GlobalId> children;
    this->reader.get<std::vector<GlobalId>>(BehaviorTreeNodeFactory::CHILDREN, children);
    for (auto child : children) {
        BehaviorTreeNodeFactory* childFactory = WorldManager::Instance()->getBehaviorTreeNodeFactory(child);
        parallelNode->addChild(childFactory->build(tientity));
    }
    return std::move(parallelNode);
}


std::unique_ptr<BehaviorTreeNode> BehaviorTreeNodeFactory::buildPrioritySelectorNode(TIEntity& tientity) {
    const std::string& name = this->reader.get<std::string>(BehaviorTreeNodeFactory::NAME, "");
    std::unique_ptr<PrioritySelectorNode> prioritySelectorNode = std::make_unique<PrioritySelectorNode>(tientity, name);
    std::vector<GlobalId> children;
    this->reader.get<std::vector<GlobalId>>(BehaviorTreeNodeFactory::CHILDREN, children);
    for (auto child : children) {
        BehaviorTreeNodeFactory* childFactory = WorldManager::Instance()->getBehaviorTreeNodeFactory(child);
        prioritySelectorNode->addChild(childFactory->build(tientity));
    }
   return std::move(prioritySelectorNode);
}

std::unique_ptr<BehaviorTreeNode> BehaviorTreeNodeFactory::buildSelectorNode(TIEntity& tientity) {
    const std::string& name = this->reader.get<std::string>(BehaviorTreeNodeFactory::NAME, "");
    std::unique_ptr<SelectorNode> selectorNode = std::make_unique<SelectorNode>(tientity, name);
    std::vector<GlobalId> children;
    this->reader.get<std::vector<GlobalId>>(BehaviorTreeNodeFactory::CHILDREN, children);
    for (auto child : children) {
        BehaviorTreeNodeFactory* childFactory = WorldManager::Instance()->getBehaviorTreeNodeFactory(child);
        selectorNode->addChild(childFactory->build(tientity));
    }
   return std::move(selectorNode);
}


std::unique_ptr<BehaviorTreeNode> BehaviorTreeNodeFactory::buildSequenceNode(TIEntity& tientity) {
    const std::string& name = this->reader.get<std::string>(BehaviorTreeNodeFactory::NAME, "");
    std::unique_ptr<SequenceNode> sequenceNode = std::make_unique<SequenceNode>(tientity, name);
    std::vector<GlobalId> children;
    this->reader.get<std::vector<GlobalId>>(BehaviorTreeNodeFactory::CHILDREN, children);
    for (auto child : children) {
        BehaviorTreeNodeFactory* childFactory = WorldManager::Instance()->getBehaviorTreeNodeFactory(child);
        sequenceNode->addChild(childFactory->build(tientity));
    }
    return std::move(sequenceNode);
}


void BehaviorTreeNodeFactory::addPreConditionDecorator(TIEntity& tientity, const ScriptTableReader& reader, BehaviorTreeNode& behaviorTreeNode) {
    std::unique_ptr<PreConditionDecorator> preConditionDecorator = make_unique<PreConditionDecorator>(tientity);
    preConditionDecorator->setPreConditonFunctionId(reader.get<GlobalId>(BehaviorTreeNodeFactory::PRE_CONDITION, 0));
    behaviorTreeNode.addPreDecorator(std::move(preConditionDecorator));
}


void BehaviorTreeNodeFactory::addPostConditionDecorator(TIEntity& tientity, const ScriptTableReader& reader, BehaviorTreeNode& behaviorTreeNode) {
    std::unique_ptr<PostConditionDecorator> postConditionDecorator = make_unique<PostConditionDecorator>(tientity);
    postConditionDecorator->setPostConditonFunctionId(reader.get<GlobalId>(BehaviorTreeNodeFactory::POST_CONDITION, 0));
    behaviorTreeNode.addPostDecorator(std::move(postConditionDecorator));
}


void BehaviorTreeNodeFactory::addOnMessageDecorator(TIEntity& tientity, const ScriptTableReader& reader, BehaviorTreeNode& behaviorTreeNode) {
    std::unique_ptr<OnMessageDecorator> onMessageDecorator = make_unique<OnMessageDecorator>(tientity);
    onMessageDecorator->setOnMessageFunctionId(reader.get<GlobalId>(BehaviorTreeNodeFactory::ON_MESSAGE, 0));
    for (auto& [index, subscriptionReader] : reader.getReaders()) {
        for (auto& [index, subscription] : subscriptionReader.getValues<float>()) {
            MessagesComponentSystem::Instance()->subscribe(tientity, subscription, std::bind(&OnMessageDecorator::onMessage, onMessageDecorator.get(), std::placeholders::_1));
        }
    }
    behaviorTreeNode.addPreDecorator(std::move(onMessageDecorator));
}


void BehaviorTreeNodeFactory::addWaitForMessageDecorator(TIEntity& tientity, const ScriptTableReader& reader, BehaviorTreeNode& behaviorTreeNode) {
    std::unique_ptr<WaitForMessageDecorator> waitForMessageDecorator = make_unique<WaitForMessageDecorator>(tientity);
    waitForMessageDecorator->setOnMessageFunctionId(reader.get<GlobalId>(BehaviorTreeNodeFactory::ON_MESSAGE, 0));
    for (auto& [index, subscriptionReader] : reader.getReaders()) {
        for (auto& [index, subscription] : subscriptionReader.getValues<float>()) {
            MessagesComponentSystem::Instance()->subscribe(tientity, subscription, std::bind(&WaitForMessageDecorator::onMessage, waitForMessageDecorator.get(), std::placeholders::_1));
        }
    }
    behaviorTreeNode.addPreDecorator(std::move(waitForMessageDecorator));
}


void BehaviorTreeNodeFactory::addLoopDecorator(TIEntity& tientity, const ScriptTableReader& reader, BehaviorTreeNode& behaviorTreeNode) {
    std::unique_ptr<LoopDecorator> loopDecorator = make_unique<LoopDecorator>(tientity);
    behaviorTreeNode.addPostDecorator(std::move(loopDecorator));
}
