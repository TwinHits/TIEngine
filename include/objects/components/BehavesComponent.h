#ifndef BEHAVESCOMPONENT_H
#define BEHAVESCOMPONENT_H

#include "objects/components/Component.h"

#include <map>
#include <memory>
#include <vector>

#include "ai/FiniteStateMachine.h"
#include "ai/behaviortree/nodes/BehaviorTreeNode.h"

namespace TIE {

class BehavesComponent : public Component {
	public:
		BehavesComponent() {};
		virtual ~BehavesComponent() {};

		std::unique_ptr<FiniteStateMachine> rootFiniteStateMachine;
		std::unique_ptr<BehaviorTreeNode> rootBehaviorTreeNode;
		GlobalId rootPayload = 0;

		std::map<GlobalId, std::vector<BehaviorTreeNode*>> subscriptions = {};
};

}
#endif
