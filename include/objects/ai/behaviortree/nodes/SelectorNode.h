#ifndef SELECTORNODE_H
#define SELECTORNODE_H

#include "objects/ai/behaviortree/nodes/BehaviorTreeNode.h"

#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class SelectorNode : public BehaviorTreeNode {
    public:
        SelectorNode(TIEntity&);

        virtual BehaviorTree::NodeStatus update(float);

    private:
        BehaviorTreeNode* resumeNode = nullptr;
};

}

#endif