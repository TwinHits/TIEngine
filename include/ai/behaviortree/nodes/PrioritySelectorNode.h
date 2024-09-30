#ifndef PRIORITYSELECTORNODE_H
#define PRIORITYSELECTORNODE_H

#include "ai/behaviortree/nodes/BehaviorTreeNode.h"

#include <string>

namespace TIE {

class PrioritySelectorNode : public BehaviorTreeNode {
    public:
        PrioritySelectorNode(TIEntity&, const std::string&);

        virtual BehaviorTree::NodeStatus update(float);
};

}

#endif