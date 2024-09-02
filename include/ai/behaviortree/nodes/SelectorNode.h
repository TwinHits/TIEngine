#ifndef SELECTORNODE_H
#define SELECTORNODE_H

#include "ai/behaviortree/nodes/BehaviorTreeNode.h"

#include <string>

#include "enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class SelectorNode : public BehaviorTreeNode {
    public:
        SelectorNode(TIEntity&, const std::string&);

        virtual BehaviorTree::NodeStatus update(float);

    private:
        BehaviorTreeNode* resumeNode = nullptr;
};

}

#endif