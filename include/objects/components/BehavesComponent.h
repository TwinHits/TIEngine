#ifndef BEHAVESCOMPONENT_H
#define BEHAVESCOMPONENT_H

#include "objects/components/Component.h"

#include <memory>

#include "objects/ai/FiniteStateMachine.h"
#include "objects/ai/behaviortree/BehaviorTreeNode.h"

namespace TIE {

class BehavesComponent : public Component {
	public:
		BehavesComponent() {};
		virtual ~BehavesComponent() {};

		std::unique_ptr<FiniteStateMachine> rootFiniteStateMachine;
		std::unique_ptr<BehaviorTreeNode> rootBehaviorTreeNode;
		GlobalId rootPayload = 0;
};

}
#endif
