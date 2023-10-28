#ifndef BEHAVIORTREENODEFACTORY_H
#define BEHAVIORTREENODEFACTORY_H

#include <sol/sol.hpp>

#include <map>
#include <memory>
#include <string>

#include "objects/GlobalId.h"
#include "objects/ai/behaviortree/BehaviorTreeNode.h"
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
		static const inline std::string HAS_EVENT_NODE = "HasEventNode";
		static const inline std::string WAIT_FOR_EVENT_NODE = "HasEventNode";

	private:
		GlobalId id = 0;
		ScriptTableReader reader;

		std::unique_ptr<BehaviorTreeNode> buildLeafNode(TIEntity&);
		std::unique_ptr<BehaviorTreeNode> buildSelectorNode(TIEntity&);
		std::unique_ptr<BehaviorTreeNode> buildSequenceNode(TIEntity&);
		std::unique_ptr<BehaviorTreeNode> buildHasEventNode(TIEntity&);
		std::unique_ptr<BehaviorTreeNode> buildWaitForEventNode(TIEntity&);

		static const inline std::string PRE_CONDITION = "preCondition";
		static const inline std::string ON_UPDATE = "update";
		static const inline std::string POST_CONDITION = "postCondition";
		static const inline std::string NODE_TYPE = "NodeType";
		static const inline std::string CHILDREN = "Children";
		static const inline std::string SUBSCRIPTIONS = "Subscriptions";

};
}

#endif BEHAVIORTREENODEFACTORY_H
