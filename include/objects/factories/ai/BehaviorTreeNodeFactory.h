#ifndef BEHAVIORTREENODEFACTORY_H
#define BEHAVIORTREENODEFACTORY_H

#include <sol/sol.hpp>

#include <map>
#include <memory>
#include <string>

#include "objects/GlobalId.h"
#include "objects/ai/behaviortree/nodes/BehaviorTreeNode.h"
#include "objects/ScriptTableReader.h"

namespace TIE {

class BehaviorTreeNodeFactory {
	public:
		BehaviorTreeNodeFactory(const sol::table&);

		std::unique_ptr<BehaviorTreeNode> build(TIEntity&);

		GlobalId getId();

		static const inline std::string LEAF_NODE = "LeafNode";
		static const inline std::string SELECTOR_NODE = "SelectorNode";
		static const inline std::string SEQUENCE_NODE = "SequenceNode";
		static const inline std::string PARALLEL_NODE = "ParallelNode";

		static const inline std::string PRE_CONDITION = "preCondition";
		static const inline std::string POST_CONDITION = "postCondition";
		static const inline std::string ON_MESSAGE = "onMessage";
		static const inline std::string WAIT_FOR_MESSAGE = "waitForMessage";
	private:
		GlobalId id = 0;
		ScriptTableReader reader;

		std::unique_ptr<BehaviorTreeNode> buildLeafNode(TIEntity&);
		std::unique_ptr<BehaviorTreeNode> buildSelectorNode(TIEntity&);
		std::unique_ptr<BehaviorTreeNode> buildSequenceNode(TIEntity&);
		std::unique_ptr<BehaviorTreeNode> buildParallelNode(TIEntity&);

		void addPreConditionDecorator(TIEntity&, const ScriptTableReader&, BehaviorTreeNode&);
		void addPostConditionDecorator(TIEntity&, const ScriptTableReader&, BehaviorTreeNode&);
		void addOnMessageDecorator(TIEntity&, const ScriptTableReader&, BehaviorTreeNode&);
		void addWaitForMessageDecorator(TIEntity&, const ScriptTableReader&, BehaviorTreeNode&);

		static const inline std::string NAME = "Name";
		static const inline std::string ON_UPDATE = "update";
		static const inline std::string NODE_TYPE = "NodeType";
		static const inline std::string CHILDREN = "Children";
		static const inline std::string SUBSCRIPTIONS = "Subscriptions";
		static const inline std::string DECORATORS = "Decorators";
		static const inline std::string DECORATOR_TYPE = "DecoratorType";

};
}

#endif BEHAVIORTREENODEFACTORY_H
